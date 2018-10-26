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
#include "AS-Config.h"
#include "AS-Context.h"
#include "S1ap-SourceeNB-ToTargeteNB-TransparentContainer.h"
#include "S1ap-Source-ToTarget-TransparentContainer.h"
#include "S1ap-E-RABInformationListItem.h"
#include "asn1_conversions.h"


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
    0, 0, //MSC_AS_TIME_ARGS(ctxt_pP),
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
    0, 0, //MSC_AS_TIME_ARGS(ctxt_pP),
    ue_ctxt_release_request_ies_p->eNB_UE_S1AP_ID,
    ue_ctxt_release_request_ies_p->mme_ue_s1ap_id);

  /* UE associated signalling -> use the allocated stream */
  s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);

  return 0;
}

//新添
int s1ap_send_handover_require(instance_t instance, s1ap_handover_req_t *s1ap_handover_req_p) {
  s1ap_message  message;
  uint8_t  *buffer;
  uint32_t length;
  s1ap_eNB_instance_t *s1ap_eNB_instance_p = NULL;
  struct s1ap_eNB_ue_context_s      *ue_context_p        = NULL;

  S1ap_HandoverRequiredIEs_t *s1ap_handover_require_ies_p = NULL;


  //获取源基站信息
  s1ap_eNB_instance_p = s1ap_eNB_get_instance(instance);
  DevAssert(s1ap_handover_req_p != NULL);
  DevAssert(s1ap_eNB_instance_p != NULL);
  printf("eNB:id:%d,modid_s:%d,modid_t:%d\n", s1ap_eNB_instance_p->eNB_id, s1ap_handover_req_p->modid_s, s1ap_handover_req_p->modid_t - 1);
  fflush(stdout);
  if ((ue_context_p = s1ap_eNB_get_ue_context(s1ap_eNB_instance_p,
                      s1ap_handover_req_p->eNB_ue_s1ap_id)) == NULL) {
    /* The context for this eNB ue s1ap id doesn't exist in the map of eNB UEs */
    S1AP_WARN("Failed to find ue context associated with eNB ue s1ap id: %u\n",
              s1ap_handover_req_p->eNB_ue_s1ap_id);
    return -1;
  }


  //TomDing 封装透传
  S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t *S1ap_SourceeNB_ToTargeteNB_TransparentContainer;
  S1ap_SourceeNB_ToTargeteNB_TransparentContainer = malloc(sizeof(S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t));
  memset(S1ap_SourceeNB_ToTargeteNB_TransparentContainer, 0, sizeof(S1ap_SourceeNB_ToTargeteNB_TransparentContainer_t));
  //TomDing 封装RRC Container
  OCTET_STRING_fromBuf(&S1ap_SourceeNB_ToTargeteNB_TransparentContainer->rRC_Container,
                       (const char*)s1ap_handover_req_p->rrc_container_buf,
                       s1ap_handover_req_p->rrc_container_len);
  printf("[HO REQUIRE] rRC_Container package success\n");
  fflush(stdout);
  //TomDing 封装e_rab
  S1ap_IE_t *ie;
  S1ap_E_RABInformationListItem_t *item;
  item = malloc(sizeof(S1ap_E_RABInformationListItem_t));
  memset(item, 0, sizeof(S1ap_E_RABInformationListItem_t));
  for (int i = 0; i < s1ap_handover_req_p->setup_e_rabs; ++i)
  {
    e_rab_t e_rab = s1ap_handover_req_p->e_rab_param[i];
    uint8_t e_rab_id = e_rab.e_rab_id;
    item->e_RAB_ID = e_rab_id;
    S1ap_DL_Forwarding_t dL_Forwarding = S1ap_DL_Forwarding_dL_Forwarding_proposed;
    item->dL_Forwarding = &dL_Forwarding;
    ie = s1ap_new_ie(S1ap_ProtocolIE_ID_id_E_RABInformationListItem,
                     S1ap_Criticality_ignore,
                     &asn_DEF_S1ap_E_RABInformationListItem,
                     item);
    if (ie != NULL) {
      ASN_SEQUENCE_ADD(&S1ap_SourceeNB_ToTargeteNB_TransparentContainer->e_RABInformationList->list, ie);
    }
  }
  printf("[HO REQUIRE] e_RABInformationList package success\n");
  fflush(stdout);
  //TomDing 封装targetCellID
  //问题：该targetCellId是目标基站小区的ID，还是源基站小区的ID
  MCC_MNC_TO_TBCD(s1ap_handover_req_p->targetMCC, s1ap_handover_req_p->targetMNC, s1ap_handover_req_p->target_MNC_Digit_Length
                  , &S1ap_SourceeNB_ToTargeteNB_TransparentContainer->targetCell_ID.pLMNidentity);
  MACRO_ENB_ID_TO_CELL_IDENTITY(s1ap_handover_req_p->targeteNBID, s1ap_handover_req_p->targetCellId,
                                &S1ap_SourceeNB_ToTargeteNB_TransparentContainer->targetCell_ID.cell_ID);
  printf("[HO REQUIRE] targetCellID package success\n");
  fflush(stdout);
  //TomDing 封装UE History
  //封装一个S1ap_LastVisitedCell_Item_t为当前访问的cell，其中time_UE_StayedInCell和cell_Size为错误信息
  S1ap_LastVisitedCell_Item_t lastVisitedCellItem;
  memset(&lastVisitedCellItem, 0, sizeof(S1ap_LastVisitedCell_Item_t));
  lastVisitedCellItem.present = S1ap_LastVisitedCell_Item_PR_e_UTRAN_Cell;
  S1ap_LastVisitedEUTRANCellInformation_t *lastVisitedCellInfo = &lastVisitedCellItem.choice.e_UTRAN_Cell;
  MCC_MNC_TO_TBCD(s1ap_eNB_instance_p->mcc, s1ap_eNB_instance_p->mnc, s1ap_eNB_instance_p->mnc_digit_length,
                  &lastVisitedCellInfo->global_Cell_ID.pLMNidentity);
  //int cell_ID=s1ap_handover_req_p->sourceCellId;
  MACRO_ENB_ID_TO_CELL_IDENTITY(s1ap_eNB_instance_p->eNB_id, s1ap_handover_req_p->sourceCellId, &lastVisitedCellInfo->global_Cell_ID.cell_ID);
  lastVisitedCellInfo->cellType.cell_Size = S1ap_Cell_Size_medium;
  lastVisitedCellInfo->time_UE_StayedInCell = 1;
  ASN_SEQUENCE_ADD(&S1ap_SourceeNB_ToTargeteNB_TransparentContainer->uE_HistoryInformation.list, &lastVisitedCellItem);
  printf("[HO REQUIRE] uE_HistoryInformation package success\n");
  fflush(stdout);


  //TomDing 封装透传信息为buffer
  uint8_t *buf;
  buf = malloc(8192);
  asn_enc_rval_t ret = uper_encode_to_buffer(&asn_DEF_S1ap_SourceeNB_ToTargeteNB_TransparentContainer, S1ap_SourceeNB_ToTargeteNB_TransparentContainer, buf, 8192);
  AssertFatal (ret.encoded > 0, "ASN1 message encoding failed (%s, %jd)!\n",
               ret.failed_type->name, ret.encoded);

  //封装S1AP_HANDOVER_REQUIRE_IES
  memset(&message, 0, sizeof(s1ap_message));
  message.direction     = S1AP_PDU_PR_initiatingMessage;
  message.procedureCode = S1ap_ProcedureCode_id_HandoverPreparation;
  s1ap_handover_require_ies_p = &message.msg.s1ap_HandoverRequiredIEs;
  s1ap_handover_require_ies_p->mme_ue_s1ap_id = ue_context_p->mme_ue_s1ap_id;
  s1ap_handover_require_ies_p->eNB_UE_S1AP_ID = ue_context_p->eNB_ue_s1ap_id;
  s1ap_handover_require_ies_p->handoverType = S1ap_HandoverType_intralte;
  s1ap_handover_require_ies_p->presenceMask = 1234;
  s1ap_handover_require_ies_p->cause.present = S1ap_Cause_PR_radioNetwork;
  s1ap_handover_require_ies_p->cause.choice.radioNetwork = S1ap_CauseRadioNetwork_s1_intra_system_handover_triggered;

  s1ap_handover_require_ies_p->targetID.present = S1ap_TargetID_PR_targeteNB_ID;

  s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.eNB_ID.present = S1ap_ENB_ID_PR_macroENB_ID;
  //封装透传信息

  OCTET_STRING_fromBuf(&s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer,
                       buf, (ret.encoded + 7) / 8);
  MACRO_ENB_ID_TO_BIT_STRING(s1ap_handover_req_p->targeteNBID,
                             &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.eNB_ID.choice.macroENB_ID);
  MCC_MNC_TO_TBCD(s1ap_handover_req_p->targetMCC, s1ap_handover_req_p->targetMNC, s1ap_handover_req_p->target_MNC_Digit_Length,
                  &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.global_ENB_ID.pLMNidentity);
  MCC_MNC_TO_PLMNID(s1ap_handover_req_p->targetMCC, s1ap_handover_req_p->targetMNC, s1ap_handover_req_p->target_MNC_Digit_Length,
                    &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.selected_TAI.pLMNidentity);
  INT16_TO_OCTET_STRING(s1ap_handover_req_p->targetTAC, &s1ap_handover_require_ies_p->targetID.choice.targeteNB_ID.selected_TAI.tAC);

  printf("eNB ue_s1ap_id:%d\neNB_id:%d\n", ue_context_p->eNB_ue_s1ap_id, s1ap_eNB_instance_p->eNB_id);

  printf("[HO REQUIRE] HANDOVER_REQUIRE_IES package success\n");
  fflush(stdout);
  if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
    S1AP_ERROR("Failed to do test\n");
    return -1;
  }
  s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);
  if (&s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf != NULL) {
    free(s1ap_handover_require_ies_p->source_ToTarget_TransparentContainer.buf);
  }
  return 1;
}
//发送handoverequest ack
int s1ap_send_handover_request_ack(uint32_t   assoc_id, uint32_t               stream, uint32_t   mme_ue_s1ap_id) {
  s1ap_message  message;
  uint8_t  *buffer;
  uint32_t length;
  s1ap_eNB_ue_context_t *ue_desc_p     = NULL;

  S1ap_HandoverRequestAcknowledgeIEs_t *s1ap_handover_request_ack_ies_p = NULL;
  S1ap_E_RABAdmittedItem_t e_RABAdmittedItem = {0};
  memset(&message, 0, sizeof(s1ap_message));

  message.direction     = S1AP_PDU_PR_successfulOutcome;
  message.procedureCode = S1ap_ProcedureCode_id_HandoverResourceAllocation;
  s1ap_handover_request_ack_ies_p = &message.msg.s1ap_HandoverRequestAcknowledgeIEs;
  s1ap_handover_request_ack_ies_p->presenceMask |= 0;

  //s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID=3;
  //s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id=4;


//    s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID= s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID;
//    s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id= s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id;
  if ((ue_desc_p = s1ap_eNB_allocate_new_UE_context()) == NULL) {
    S1AP_ERROR("Cannot allocate new ue context\n");
    return -1;
  }
  s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID = ue_desc_p->eNB_ue_s1ap_id;
  s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id = mme_ue_s1ap_id;
  printf("TomDing Request ACK mme_ue_s1ap_id:%d,eNB_ue_s1ap_id:%d\n", s1ap_handover_request_ack_ies_p->mme_ue_s1ap_id, s1ap_handover_request_ack_ies_p->eNB_UE_S1AP_ID);
  printf("wujinwo_send_handover_request_ack3\n");
  fflush(stdout);

  e_RABAdmittedItem.e_RAB_ID = 5;
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
    uint32_t ip_address = calloc (1, sizeof (uint32_t));
    ip_address = 0x6956BB78;

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
  printf("magicwo_send_ack_assoc_id", assoc_id);
  printf("magicwo_send_ack_stream", stream);
  fflush(stdout);
  s1ap_eNB_itti_send_sctp_data_req(0,
                                   assoc_id, buffer,
                                   length, stream);

  return 1;
}
//write by coco send notify
int s1ap_send_handover_notify(instance_t instance, s1ap_handover_notify_t *s1ap_handover_notify_p) {
  s1ap_message  message;
  uint8_t  *buffer;
  uint32_t length;
  s1ap_eNB_instance_t *s1ap_eNB_instance_p = NULL;
  struct s1ap_eNB_ue_context_s      *ue_context_p        = NULL;

  S1ap_HandoverNotifyIEs_t *s1ap_handover_notify_ies_p = NULL;
  //get eNB_ue_s1ap_id
  s1ap_eNB_instance_p = s1ap_eNB_get_instance(instance);
  DevAssert(s1ap_handover_notify_p != NULL);
  DevAssert(s1ap_eNB_instance_p != NULL);
  if ((ue_context_p = s1ap_eNB_get_ue_context(s1ap_eNB_instance_p,
                      s1ap_handover_notify_p->eNB_ue_s1ap_id)) == NULL) {
    /* The context for this eNB ue s1ap id doesn't exist in the map of eNB UEs */
    S1AP_WARN("Failed to find ue context associated with eNB ue s1ap id: %u\n",
              s1ap_handover_notify_p->eNB_ue_s1ap_id);
    return -1;
  }

  memset(&message, 0, sizeof(s1ap_message));
  message.direction     = S1AP_PDU_PR_initiatingMessage;
  message.procedureCode = S1ap_ProcedureCode_id_HandoverNotification;
  s1ap_handover_notify_ies_p = &message.msg.s1ap_HandoverNotifyIEs;
  //tianbaowen
  s1ap_handover_notify_ies_p->mme_ue_s1ap_id = ue_context_p->mme_ue_s1ap_id;
  s1ap_handover_notify_ies_p->eNB_UE_S1AP_ID = ue_context_p->eNB_ue_s1ap_id;
  //EUTRAN cgi
  MCC_MNC_TO_PLMNID(
    s1ap_eNB_instance_p->mcc,
    s1ap_eNB_instance_p->mnc,
    s1ap_eNB_instance_p->mnc_digit_length,
    &s1ap_handover_notify_ies_p->eutran_cgi.pLMNidentity);
  MACRO_ENB_ID_TO_CELL_IDENTITY(s1ap_eNB_instance_p->eNB_id,
                                0,
                                &s1ap_handover_notify_ies_p->eutran_cgi.cell_ID);
  //TAI
  MCC_MNC_TO_PLMNID(
    s1ap_eNB_instance_p->mcc,
    s1ap_eNB_instance_p->mnc,
    s1ap_eNB_instance_p->mnc_digit_length,
    &s1ap_handover_notify_ies_p->tai.pLMNidentity);
  TAC_TO_ASN1(s1ap_eNB_instance_p->tac, &s1ap_handover_notify_ies_p->tai.tAC);

  printf("eNB ue_s1ap_id:%d\n", ue_context_p->eNB_ue_s1ap_id);

  printf("Trying to send handover_notify in context_management by coco\n");


  if (s1ap_eNB_encode_pdu(&message, &buffer, &length) < 0) {
    /* Encode procedure has failed... */
    S1AP_ERROR("Failed to do handover_notify sending\n");
    return -1;
  }
  printf("step4 trying to send notify\n");
  fflush(stdout);
  s1ap_eNB_itti_send_sctp_data_req(s1ap_eNB_instance_p->instance,
                                   ue_context_p->mme_ref->assoc_id, buffer,
                                   length, ue_context_p->tx_stream);
  return 1;
}
int s1ap_send_rrc_connection_reconfiguration(S1ap_HandoverCommandIEs_t *handoverCommand_p, uint32_t   assoc_id, uint32_t stream) {
  MessageDef *msg_p;
  s1ap_eNB_mme_data_t   *mme_desc_p       = NULL;
  s1ap_eNB_ue_context_t *ue_desc_p        = NULL;
  MessageDef            *message_p        = NULL;
  if ((mme_desc_p = s1ap_eNB_get_MME(NULL, assoc_id, 0)) == NULL) {
    S1AP_ERROR("[SCTP %d] Received initial context setup request for non "
               "existing MME context TomDing\n", assoc_id);
    return -1;
  }
  printf("TomDing s1ap_eNB_instance : %d\n", mme_desc_p->s1ap_eNB_instance);
  if ((ue_desc_p = s1ap_eNB_get_ue_context(mme_desc_p->s1ap_eNB_instance,
                   handoverCommand_p->eNB_UE_S1AP_ID)) == NULL) {
    S1AP_ERROR("[SCTP %d] Received initial context setup request for non "
               "existing UE context  TomDing 0x%06lx\n", assoc_id,
               handoverCommand_p->eNB_UE_S1AP_ID);
    return -1;
  }
  printf("TomDing ue_desc_p->mme_ue_s1ap_id=%d,ue_initial_id=%d\n", ue_desc_p->mme_ue_s1ap_id, ue_desc_p->ue_initial_id);
  ue_desc_p->rx_stream = stream;
  msg_p = itti_alloc_new_message(TASK_S1AP, S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER);
  S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER(msg_p).ue_initial_id = ue_desc_p->ue_initial_id;
  ue_desc_p->ue_initial_id = 0;
  S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER(msg_p).eNB_ue_s1ap_id = handoverCommand_p->eNB_UE_S1AP_ID;
  LOG_I(RRC, "We DO TEST SENDING S1AP_RRCCONNECTION_RECONFIGURATION_HANDOVER\n");
  fflush(stdout);
  itti_send_msg_to_task(TASK_RRC_ENB, 0, msg_p);
  return 0;
}


