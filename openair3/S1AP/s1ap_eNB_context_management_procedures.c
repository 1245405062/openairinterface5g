/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.0  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file s1ap_eNB_context_management_procedures.c
 * \brief S1AP context management procedures 
 * \author  S. Roux and Navid Nikaein 
 * \date 2010 - 2015
 * \email: navid.nikaein@eurecom.fr
 * \version 1.0
 * @ingroup _s1ap
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "assertions.h"
#include "conversions.h"

#include "intertask_interface.h"

#include "s1ap_common.h"
#include "s1ap_eNB_defs.h"

#include "s1ap_eNB_itti_messaging.h"

#include "s1ap_ies_defs.h"
#include "s1ap_eNB_encoder.h"
#include "s1ap_eNB_nnsf.h"
#include "s1ap_eNB_ue_context.h"
#include "s1ap_eNB_nas_procedures.h"
#include "s1ap_eNB_management_procedures.h"
#include "s1ap_eNB_context_management_procedures.h"
#include "msc.h"
#include "s1ap_messages_types.h"

int s1ap_ue_context_release_complete(instance_t instance,
                                     s1ap_ue_release_complete_t *ue_release_complete_p)
{
  s1ap_eNB_instance_t          *s1ap_eNB_instance_p = NULL;
  struct s1ap_eNB_ue_context_s *ue_context_p        = NULL;

  S1ap_UEContextReleaseCompleteIEs_t *ue_ctxt_release_complete_ies_p = NULL;

  s1ap_message  message;

  uint8_t  *buffer;
  uint32_t length;
  int      ret = -1;

  /* Retrieve the S1AP eNB instance associated with Mod_id */
  s1ap_eNB_instance_p = s1ap_eNB_get_instance(instance);

  DevAssert(ue_release_complete_p != NULL);
  DevAssert(s1ap_eNB_instance_p != NULL);

  /*RB_FOREACH(ue_context_p, s1ap_ue_map, &s1ap_eNB_instance_p->s1ap_ue_head) {
	  S1AP_WARN("in s1ap_ue_map: UE context eNB_ue_s1ap_id %u mme_ue_s1ap_id %u state %u\n",
			  ue_context_p->eNB_ue_s1ap_id, ue_context_p->mme_ue_s1ap_id,
			  ue_context_p->ue_state);
  }*/
  if ((ue_context_p = s1ap_eNB_get_ue_context(s1ap_eNB_instance_p,
                      ue_release_complete_p->eNB_ue_s1ap_id)) == NULL) {
    /* The context for this eNB ue s1ap id doesn't exist in the map of eNB UEs */
    S1AP_WARN("Failed to find ue context associated with eNB ue s1ap id: %u\n",
              ue_release_complete_p->eNB_ue_s1ap_id);
    return -1;
  }

  /* Prepare the S1AP message to encode */
  memset(&message, 0, sizeof(s1ap_message));

  message.direction     = S1AP_PDU_PR_successfulOutcome;
  message.procedureCode = S1ap_ProcedureCode_id_UEContextRelease;
  //message.criticality   = S1ap_Criticality_reject;

  ue_ctxt_release_complete_ies_p = &message.msg.s1ap_UEContextReleaseCompleteIEs;

  ue_ctxt_release_complete_ies_p->eNB_UE_S1AP_ID = ue_release_complete_p->eNB_ue_s1ap_id;
  ue_ctxt_release_complete_ies_p->mme_ue_s1ap_id = ue_context_p->mme_ue_s1ap_id;
  //ue_ctxt_release_complete_ies_p->criticalityDiagnostics
  //ue_ctxt_release_complete_ies_p->presenceMask

  if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
    /* Encode procedure has failed... */
    S1AP_ERROR("Failed to encode UE context release complete\n");
    return -1;
  }

  MSC_LOG_TX_MESSAGE(
    MSC_S1AP_ENB,
    MSC_S1AP_MME,
    buffer,
    length,
    MSC_AS_TIME_FMT" UEContextRelease successfulOutcome eNB_ue_s1ap_id %u mme_ue_s1ap_id %u",
    0,0, //MSC_AS_TIME_ARGS(ctxt_pP),
    ue_ctxt_release_complete_ies_p->eNB_UE_S1AP_ID,
    ue_ctxt_release_complete_ies_p->mme_ue_s1ap_id);

  /* UE associated signalling -> use the allocated stream */
  s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);


  //LG s1ap_eNB_itti_send_sctp_close_association(s1ap_eNB_instance_p->instance,
  //                                 ue_context_p->mme_ref->assoc_id);



  // release UE context
  struct s1ap_eNB_ue_context_s *ue_context2_p = NULL;

  if ((ue_context2_p = RB_REMOVE(s1ap_ue_map, &s1ap_eNB_instance_p->s1ap_ue_head, ue_context_p))
      != NULL) {
    S1AP_WARN("Removed UE context eNB_ue_s1ap_id %u\n",
              ue_context2_p->eNB_ue_s1ap_id);
    s1ap_eNB_free_ue_context(ue_context2_p);
  } else {
    S1AP_WARN("Removing UE context eNB_ue_s1ap_id %u: did not find context\n",
              ue_context_p->eNB_ue_s1ap_id);
  }
  /*RB_FOREACH(ue_context_p, s1ap_ue_map, &s1ap_eNB_instance_p->s1ap_ue_head) {
	  S1AP_WARN("in s1ap_ue_map: UE context eNB_ue_s1ap_id %u mme_ue_s1ap_id %u state %u\n",
			  ue_context_p->eNB_ue_s1ap_id, ue_context_p->mme_ue_s1ap_id,
			  ue_context_p->ue_state);
  }*/

  return ret;
}


int s1ap_ue_context_release_req(instance_t instance,
                                s1ap_ue_release_req_t *ue_release_req_p)
{
  s1ap_eNB_instance_t               *s1ap_eNB_instance_p           = NULL;
  struct s1ap_eNB_ue_context_s      *ue_context_p                  = NULL;
  S1ap_UEContextReleaseRequestIEs_t *ue_ctxt_release_request_ies_p = NULL;
  s1ap_message                       message;
  uint8_t                           *buffer                        = NULL;
  uint32_t                           length;

  /* Retrieve the S1AP eNB instance associated with Mod_id */
  s1ap_eNB_instance_p = s1ap_eNB_get_instance(instance);

  DevAssert(ue_release_req_p != NULL);
  DevAssert(s1ap_eNB_instance_p != NULL);

  if ((ue_context_p = s1ap_eNB_get_ue_context(s1ap_eNB_instance_p,
                      ue_release_req_p->eNB_ue_s1ap_id)) == NULL) {
    /* The context for this eNB ue s1ap id doesn't exist in the map of eNB UEs */
    S1AP_WARN("Failed to find ue context associated with eNB ue s1ap id: %u\n",
              ue_release_req_p->eNB_ue_s1ap_id);
    return -1;
  }

  /* Prepare the S1AP message to encode */
  memset(&message, 0, sizeof(s1ap_message));

  message.direction     = S1AP_PDU_PR_initiatingMessage;
  message.procedureCode = S1ap_ProcedureCode_id_UEContextReleaseRequest;
  //message.criticality   = S1ap_Criticality_reject;

  ue_ctxt_release_request_ies_p = &message.msg.s1ap_UEContextReleaseRequestIEs;

  ue_ctxt_release_request_ies_p->eNB_UE_S1AP_ID = ue_release_req_p->eNB_ue_s1ap_id;
  ue_ctxt_release_request_ies_p->mme_ue_s1ap_id = ue_context_p->mme_ue_s1ap_id;

  switch (ue_release_req_p->cause) {
  case S1AP_CAUSE_NOTHING:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_NOTHING;
    break;

  case S1AP_CAUSE_RADIO_NETWORK:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_radioNetwork;
    ue_ctxt_release_request_ies_p->cause.choice.radioNetwork = ue_release_req_p->cause_value;
    break;

  case S1AP_CAUSE_TRANSPORT:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_transport;
    ue_ctxt_release_request_ies_p->cause.choice.transport = ue_release_req_p->cause_value;
    break;

  case S1AP_CAUSE_NAS:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_nas;
    ue_ctxt_release_request_ies_p->cause.choice.nas = ue_release_req_p->cause_value;
    break;

  case S1AP_CAUSE_PROTOCOL:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_protocol;
    ue_ctxt_release_request_ies_p->cause.choice.protocol = ue_release_req_p->cause_value;
    break;

  case S1AP_CAUSE_MISC:
  default:
    ue_ctxt_release_request_ies_p->cause.present = S1ap_Cause_PR_misc;
    ue_ctxt_release_request_ies_p->cause.choice.misc = ue_release_req_p->cause_value;
    break;
  }

  if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
    /* Encode procedure has failed... */
    S1AP_ERROR("Failed to encode UE context release complete\n");
    return -1;
  }

  MSC_LOG_TX_MESSAGE(
    MSC_S1AP_ENB,
    MSC_S1AP_MME,
    buffer,
    length,
    MSC_AS_TIME_FMT" UEContextReleaseRequest initiatingMessage eNB_ue_s1ap_id %u mme_ue_s1ap_id %u",
    0,0,//MSC_AS_TIME_ARGS(ctxt_pP),
    ue_ctxt_release_request_ies_p->eNB_UE_S1AP_ID,
    ue_ctxt_release_request_ies_p->mme_ue_s1ap_id);

  /* UE associated signalling -> use the allocated stream */
  s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);

  return 0;
}

//新添
int test_send(instance_t instance,s1ap_handover_req_t *s1ap_handover_req_p){
    s1ap_message  message;
    uint8_t  *buffer;
    uint32_t length;
    s1ap_eNB_instance_t *s1ap_eNB_instance_p = NULL;
    struct s1ap_eNB_ue_context_s      *ue_context_p        = NULL;

    S1ap_HandoverRequiredIEs_t *s1ap_handover_require_ies_p = NULL;
   
    s1ap_eNB_instance_p = s1ap_eNB_get_instance(instance);
    DevAssert(s1ap_handover_req_p != NULL);
    DevAssert(s1ap_eNB_instance_p != NULL);

    if ((ue_context_p = s1ap_eNB_get_ue_context(s1ap_eNB_instance_p,
                      s1ap_handover_req_p->eNB_ue_s1ap_id)) == NULL) {
    /* The context for this eNB ue s1ap id doesn't exist in the map of eNB UEs */
    S1AP_WARN("Failed to find ue context associated with eNB ue s1ap id: %u\n",
              s1ap_handover_req_p->eNB_ue_s1ap_id);
    return -1;
    }

    printf("s1ap total numbers of setup_e_rabs %x\n",s1ap_handover_req_p->setup_e_rabs);
    printf("s1ap total numbers of e_rab to be setup in the list %x\n",s1ap_handover_req_p->nb_of_e_rabs);
   // printf("s1ap e_rab_id is %x\n",s1ap_handover_req_p->e_rab_param[0].e_rab_id);

    memset(&message, 0, sizeof(s1ap_message));
    message.direction     = S1AP_PDU_PR_initiatingMessage;
    message.procedureCode = S1ap_ProcedureCode_id_HandoverPreparation;
    s1ap_handover_require_ies_p = &message.msg.s1ap_HandoverRequiredIEs;
    s1ap_handover_require_ies_p->mme_ue_s1ap_id = s1ap_handover_req_p->mme_ue_s1ap_id;
    s1ap_handover_require_ies_p->eNB_UE_S1AP_ID = ue_context_p->eNB_ue_s1ap_id;
    s1ap_handover_require_ies_p->handoverType = 1;
    s1ap_handover_require_ies_p->presenceMask = 1234;
    s1ap_handover_require_ies_p->cause.present = S1ap_Cause_PR_radioNetwork;
    s1ap_handover_require_ies_p->cause.choice.radioNetwork = s1ap_handover_req_p->cause_value;

    s1ap_handover_require_ies_p->targetID.present = S1ap_TargetID_PR_targeteNB_ID;
    
    s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.eNB_ID.present = S1ap_ENB_ID_PR_macroENB_ID;

    MACRO_ENB_ID_TO_BIT_STRING(s1ap_eNB_instance_p->eNB_id, //instance->eNB_id
                             &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.eNB_ID.choice.macroENB_ID);
    MCC_MNC_TO_PLMNID(s1ap_eNB_instance_p->mcc, s1ap_eNB_instance_p->mnc, s1ap_eNB_instance_p->mnc_digit_length,
                      &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.pLMNidentity);
    MCC_MNC_TO_PLMNID(s1ap_eNB_instance_p->mcc, s1ap_eNB_instance_p->mnc, s1ap_eNB_instance_p->mnc_digit_length,
                      &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.selected_TAI.pLMNidentity);
    INT16_TO_OCTET_STRING(s1ap_eNB_instance_p->tac, &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.selected_TAI.tAC);

        printf("eNB ue_s1ap_id:%d\n",ue_context_p->eNB_ue_s1ap_id);	
    //s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf = calloc(3, sizeof(uint8_t));
    //s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf[0] = 0x01;
    //s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf[1] = 0x02;
    //s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf[2] = 0x03;
    //s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.size = 3;
	/* Old Code
    s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf = malloc(sizeof(s1ap_handover_req_t)); 
    memcpy(s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf,s1ap_handover_req_p,sizeof(s1ap_handover_req_t));
    s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.size = sizeof(s1ap_handover_req_t);
    */
	//pkg the S1ap-SourceeNB-ToTargeteNB-TransparentContainer.h
	S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t  *S1ap_SourceeNB_ToTargeteNB_TransparentContainer_p=(S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t*)malloc(sizeof(S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t));
	
	HandoverPreparationInformation_v14x0_IEs_t *HandoverPreparationInformation_v14x0_IEs_p=(HandoverPreparationInformation_v14x0_IEs_t*)malloc(sizeof(HandoverPreparationInformation_v14x0_IEs_t));
	memset(HandoverPreparationInformation_v14x0_IEs_p,0,sizeof(HandoverPreparationInformation_v14x0_IEs_t));
	S1ap_SourceeNB_ToTargeteNB_TransparentContainer_p->rRC_Container=(S1ap_RRC_Container_t)HandoverPreparationInformation_v14x0_IEs_p;

	S1ap_SourceeNB_ToTargeteNB_TransparentContainer_p->targetCell_ID.pLMNidentity=0x208A93;
	S1ap_SourceeNB_ToTargeteNB_TransparentContainer_p->targetCell_ID.cell_ID=0x208A93;

	
	
    if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
        /* Encode procedure has failed... */
        S1AP_ERROR("Failed to do test\n");
        return -1;
    }
    s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);
    if(&s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf != NULL){
        free(s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf);
    }
    return 1;
}
//����handoverequest ack
int s1ap_send_handover_request_ack(uint32_t   assoc_id,uint32_t               stream){
    s1ap_message  message;
    uint8_t  *buffer;
    uint32_t length;
   
  	printf("wujinwo_send_handover_request_ack1\n");
	fflush(stdout);
    S1ap_HandoverRequestAcknowledgeIEs_t *s1ap_handover_request_ack_ies_p = NULL;
    S1ap_E_RABAdmittedItem_t e_RABAdmittedItem={0};
	printf("wujinwo_send_handover_request_ack2\n");
	fflush(stdout);
    memset(&message, 0, sizeof(s1ap_message));
    message.direction     = S1AP_PDU_PR_successfulOutcome;
    message.procedureCode = S1ap_ProcedureCode_id_HandoverResourceAllocation;
    s1ap_handover_request_ack_ies_p = &message.msg.s1ap_HandoverRequestAcknowledgeIEs;
    s1ap_handover_request_ack_ies_p->presenceMask |= 0;
    s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID=3;
	s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id=4;
	printf("wujinwo_send_handover_request_ack3\n");
		fflush(stdout);
	e_RABAdmittedItem.e_RAB_ID=5;
	/*
	   * Set the GTP-TEID. This is the S1-U S-GW TEID
	   */
   INT32_TO_OCTET_STRING (1, &e_RABAdmittedItem.gTP_TEID);
	/*
   * S-GW IP address(es) for user-plane
   */
  if (1) {
    printf("wujinwo_send_handover_request_ack4\n");
	fflush(stdout);
    e_RABAdmittedItem.transportLayerAddress.buf = calloc (4, sizeof (uint8_t));
	
	printf("wujinwo_send_handover_request_ack5\n");
		fflush(stdout);
    /*
     * Only IPv4 supported
     */
	uint32_t ip_address=calloc (1, sizeof (uint32_t));
	ip_address=0x6956BB78;
	
    memcpy (e_RABAdmittedItem.transportLayerAddress.buf, &ip_address, 4);
	
	printf("wujinwo_send_handover_request_ack6\n");
		fflush(stdout);
	
    e_RABAdmittedItem.transportLayerAddress.size = 4;
    e_RABAdmittedItem.transportLayerAddress.bits_unused = 0;
  }
  ASN_SEQUENCE_ADD (&s1ap_handover_request_ack_ies_p->e_RABAdmittedList, &e_RABAdmittedItem);
   
   printf("wujinwo_send_handover_request_ack7\n");
	   fflush(stdout);
    if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
        /* Encode procedure has failed... */
        S1AP_ERROR("Failed to do test\n");
        return -1;
    }
	printf("magicwo_send_ack_assoc_id",assoc_id);	
	printf("magicwo_send_ack_stream",stream);	
	fflush(stdout);
    s1ap_eNB_itti_send_sctp_data_req(0,
                                   assoc_id, buffer,
                                   length, stream);
  
    return 1;
}

int s1ap_send_rrc_connection_reconfiguration(uint32_t   assoc_id,uint32_t stream){
    MessageDef *msg_p;
    msg_p = itti_alloc_new_message(TASK_S1AP, S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER);

    S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER(msg_p).eNB_ue_s1ap_id = 1;
    LOG_I(RRC, "We DO TEST SENDING S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER\n");
    itti_send_msg_to_task(TASK_RRC_ENB,0, msg_p);
    return 0;
}


