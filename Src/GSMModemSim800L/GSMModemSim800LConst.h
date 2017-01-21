#pragma once

namespace GSMModemSim800L
{
static const char sc_RAW_DATA[]					= {"DATA"};

static const char sc_CME_errorCode[] 		= {"ERROR_CODE"};

static const char sc_CLIP_number[] 			= {"ORG_NUMBER"};
static const char sc_CLIP_type[] 				= {"TYPE"};
static const char sc_CLIP_subaddr[] 		= {"SUBADDR"};
static const char sc_CLIP_hrNumber[] 		= {"SA_TYPE"};
static const char sc_CLIP_alphaID[]			=	{"ALPHA_ID"};
static const char sc_CLIP_cliValidity[]	= {"CLI_VALIDITY"};

static const char sc_CPIN_pin[]					= {"PIN"};

static const char sc_ATD_trgtNumber[]		= {"V_DST_NUMBER"};

static const char sc_CMGS_trgtNumber[]	= {"T_DST_NUMBER"};
static const char sc_CMGS_msgText[]			= {"O_SMS_TEXT"};

static const char sc_CMTI_memoryKind[]	= {"MEMORY"};
static const char sc_CMTI_index[]				= {"INDEX"};

static const char sc_CMGL_msgId[]				= {"INC_MSG_ID"};
static const char sc_CMGL_msgState[]		= {"INC_MSG_STATE"};
static const char sc_CMGL_msgOrgNo[]		= {"INC_MSG_ORG_NO"};
static const char sc_CMGL_msgOrgNoTxt[]	= {"INC_PHONE_NUMBER_NAME"};
static const char sc_CMGL_msgTimeStamp[]= {"MSG_TIMESTAMP"};
static const char sc_CMGL_msgContent[]	= {"INC_MSG_TEXT"};

static const char sc_CPIN_simStatus[]		= {"SIM_STATUS"};

static const char sc_CREG_regMode[]			= {"REG_MODE"};
static const char sc_CREG_regStatus[]		= {"REG_STATUS"};
static const char sc_CREG_lac[]					= {"REG_LAC"};
static const char sc_CREG_ci[]					= {"REG_CI"};

static const char sc_CSQ_rssi[]					= {"RSSI"};
static const char sc_CSQ_ber[]					= {"BER"};

static const char sc_COPS_operatorName[]= {"OPERATOR_NAME"};
static const char sc_COPS_operatorFormat[]= {"OPERATOR_FORMAT"};
static const char sc_COPS_operatorState[]= {"OPERATOR_STAT"};
}
