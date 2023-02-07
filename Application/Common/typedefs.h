/********************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************
 *********************************************************************
 * File Name    : typedefs.h
 * Version      : 
 * Description  : 
 * Creation Date: Nov 25, 2022
 * Author		: KarimHmidi
 *********************************************************************/

#ifndef COMMON_TYPEDEFS_H_
#define COMMON_TYPEDEFS_H_

/*
 *
 * Includes
 *
 *********************************************************************/

/*
 *
 * Defines
 *
 **********************************************************************/

/*
 *
 * Typedefs
 *
 **********************************************************************/

/**/
typedef union ENCODER_POS {
	uint8_t all[4];
	uint32_t value;

	struct {
		uint32_t LSB:8;
		uint32_t MLB:8;
		uint32_t MHB:8;
		uint32_t MSB:8;
	}byte;

} ENCODER_POS_U;

/**/
typedef union ALL_ENCODERS_POS {
	uint32_t all[12];

	struct {
		ENCODER_POS_U _1;
		ENCODER_POS_U _2;
		ENCODER_POS_U _3;
		ENCODER_POS_U _4;
		ENCODER_POS_U _5;
		ENCODER_POS_U _6;
		ENCODER_POS_U _7;
		ENCODER_POS_U _8;
		ENCODER_POS_U _9;
		ENCODER_POS_U _10;
		ENCODER_POS_U _11;
		ENCODER_POS_U _12;
	} encoder;

} ALL_ENCODERS_POS_U;

/**/
typedef struct ENCODER_UDP {

	union {
		uint8_t all[3];
		struct {
			uint8_t HB;
			uint8_t MB;
			uint8_t LB;
		} byte;
	} position;

	union {
		uint8_t all[2];
		uint16_t value;
		struct {
			uint8_t HB;
			uint8_t LB;
		} byte;
	} speed;

	union{
		uint8_t value;
		struct {
			uint8_t encoder_type:4;
			uint8_t assigned_axis:3;
			uint8_t process_encoder:1;
		} chunk;
	} status_1;

	union {
		uint8_t value;
		struct {
			uint8_t referanceable:1;
			uint8_t referanced:1;
			uint8_t enc_read_quality:6;
		} chunk;
	}status_2;

	uint8_t status_3;
	uint8_t status_4;
	uint8_t status_5;

} ENCODER_S;

/**/
typedef union DINA_TO_LJU_CYCLIC_FRAME_Tx {

	uint8_t frame[202];

	struct {
		uint8_t addr_lju;
		uint8_t addr_dina;
		uint8_t message_id;
		uint8_t message_length;

		struct {
			uint8_t alive_cnt:7;
			uint8_t always_one:1;
		} message_cnt;

		struct {
			uint8_t error:1;
			uint8_t sys_status:3;
			uint8_t reserved:4;
		} dina_status;

		struct {
			uint8_t error_group_nr:3;
			uint8_t reserved:5;
		} dina_error_group;

		struct {
			uint16_t error_nr:14;
			uint16_t always_zero:2;
		} dina_error;

		uint8_t logic_data[64];
		uint8_t reserved[5];

		ENCODER_S encoder_1;
		ENCODER_S encoder_2;
		ENCODER_S encoder_3;
		ENCODER_S encoder_4;
		ENCODER_S encoder_5;
		ENCODER_S encoder_6;
		ENCODER_S encoder_7;
		ENCODER_S encoder_8;
		ENCODER_S encoder_9;
		ENCODER_S encoder_10;
		ENCODER_S encoder_11;
		ENCODER_S encoder_12;

		union {
			uint16_t value;
			struct {
				uint8_t HB;
				uint8_t LB;
			} byte;
		} frame_crc;
	} data;

} DINA_TO_LJU_CYCLIC_FRAME_Tx_U;

/**/
typedef union ENCODER_ZMV {

	uint8_t all[8];

	struct {
		uint8_t pos_LSB;
		uint8_t pos_MLB;
		uint8_t pos_MHB;
		uint8_t pos_MSB;
//		uint8_t pos_MSB;
//		uint8_t pos_MHB;
//		uint8_t pos_MLB;
//		uint8_t pos_LSB;
		uint8_t speed_MSB;
		uint8_t speed_LSB;
		uint8_t status_2;
		uint8_t status_1;
	} byte;

	struct {
		uint32_t pos;
		uint16_t speed;
		uint8_t status_1;
		uint8_t status_2;
	} value;

	struct {
		uint32_t pos_shit:8;
		uint32_t the_pos:24;
		uint16_t speed;
		uint8_t status_2;
		uint8_t status_1;
	} parser;

} ENCODER_U;

/**/
typedef union ZMV_CAN_FRAME_Rx {

	uint8_t frame[64];

	struct {
		union {
			uint8_t dina_std[8];
			struct {
				uint8_t B1;
				uint8_t B2;
				uint8_t B3;
				uint8_t B4;
				uint8_t B5;
				uint8_t B6;
				uint8_t B7;
				uint8_t B8;
			} bytes;
		} designer;

		union {
			uint8_t dina_err[8];
			struct {
				uint8_t B1;
				uint8_t B2;
				uint8_t B3;
				uint8_t B4;
				uint8_t B5;
				uint8_t B6;
				uint8_t B7;
				uint8_t B8;
			} byte;
		} error;

		ENCODER_U encoder_1;
		ENCODER_U encoder_2;
		ENCODER_U encoder_3;
		ENCODER_U encoder_4;
		ENCODER_U encoder_5;
		ENCODER_U encoder_6;

	} data;

} ZMV_CAN_FRAME_Rx_U;

/**/
typedef struct FBV_IN_BYTE {
	uint8_t fbi1:1;
	uint8_t fbi2:1;
	uint8_t fbi3:1;
	uint8_t fbi4:1;
	uint8_t fbi5:1;
	uint8_t fbi6:1;
	uint8_t fbi7:1;
	uint8_t fbi8:1;
} FBV_IN_BYTE_S;

/**/
typedef union FBV_ZOMBIE {
	uint8_t all[8];

	struct {
		FBV_IN_BYTE_S B1;
		FBV_IN_BYTE_S B2;
		FBV_IN_BYTE_S B3;
		FBV_IN_BYTE_S B4;
		FBV_IN_BYTE_S B5;
		FBV_IN_BYTE_S B6;
		FBV_IN_BYTE_S B7;
		FBV_IN_BYTE_S B8;
	} byte;

} FBV_ZOMBIE_U;

/**/
//typedef struct ENCODER {
//
//	union {
//		uint8_t ALL[3];
//		struct {
//			uint8_t HB;
//			uint8_t MB;
//			uint8_t LB;
//		} BYTE;
//	} POSITION;
//
//	union {
//		uint8_t ALL[2];
//		struct {
//			uint8_t HB;
//			uint8_t LB;
//		} BYTE;
//	} SPEED;
//
//	struct {
//		uint8_t ENCODER_TYPE:4;
//		uint8_t ASSIGNED_AXIS:3;
//		uint8_t PROCESS_ENCODER:1;
//	} STATUS_1;
//
//	struct {
//		uint8_t REFERANCEABLE:1;
//		uint8_t REFERANCED:1;
//		uint8_t ENCO_READ_QUALITY:6;
//	} STATUS_2;
//
//	uint8_t STATUS_3;
//	uint8_t STATUS_4;
//	uint8_t STATUS_5;
//
//} ENCODER_U;

/**/
//typedef union DINA_TO_LJU_CYCLIC_FRAME_Tx {
//
//	uint8_t FRAME[202];
//
//	struct {
//		uint8_t ADDR_LJU;
//		uint8_t ADDR_DINA;
//		uint8_t MESSAGE_ID;
//		uint8_t MESSAGE_LENGTH;
//
//		struct {
//			uint8_t ALIVE_CNT:7;
//			uint8_t ALWAYS_ONE:1;
//		} MESSAGE_CNT;
//
//		struct {
//			uint8_t ERROR:1;
//			uint8_t SYS_STATUS:3;
//			uint8_t RESERVED:4;
//		} DINA_STATUS;
//
//		struct {
//			uint8_t ERROR_GROUP_NR:3;
//			uint8_t RESERVED:5;
//		} DINA_ERROR_GROUP;
//
//		struct {
//			uint16_t ERROR_NR:14;
//			uint16_t ALWAYS_ZERO:2;
//		} DINA_ERROR;
//
//		uint8_t LOGIC_DATA[64];
//		uint8_t RESERVED[5];
//
//		ENCODER_U ENCODER_1;
//		ENCODER_U ENCODER_2;
//		ENCODER_U ENCODER_3;
//		ENCODER_U ENCODER_4;
//		ENCODER_U ENCODER_5;
//		ENCODER_U ENCODER_6;
//		ENCODER_U ENCODER_7;
//		ENCODER_U ENCODER_8;
//		ENCODER_U ENCODER_9;
//		ENCODER_U ENCODER_10;
//		ENCODER_U ENCODER_11;
//		ENCODER_U ENCODER_12;
//
//		union {
//			uint16_t ALL;
//			struct {
//				uint8_t HB;
//				uint8_t LB;
//			} BYTE;
//		} FRAME_CRC;
//	} DATA;
//
//} DINA_TO_LJU_CYCLIC_FRAME_Tx_U;

/**/
//typedef union ZMV_CAN_FRAME_Rx {
//
//	uint8_t FRAME[64];
//
//	struct {
//		union {
//			uint8_t DINA_STD[8];
//			struct {
//				uint8_t B1;
//				uint8_t B2;
//				uint8_t B3;
//				uint8_t B4;
//				uint8_t B5;
//				uint8_t B6;
//				uint8_t B7;
//				uint8_t B8;
//			} BYTES;
//		} DESIGNER;
//
//		union {
//			uint8_t DINA_ERR[8];
//			struct {
//				uint8_t B1;
//				uint8_t B2;
//				uint8_t B3;
//				uint8_t B4;
//				uint8_t B5;
//				uint8_t B6;
//				uint8_t B7;
//				uint8_t B8;
//			} BYTES;
//		} ERROR;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t POS_LSB;
//				uint8_t POS_MLB;
//				uint8_t POS_MHB;
//				uint8_t POS_MSB;
//				uint8_t SPEED_LSB;
//				uint8_t SPEED_HSB;
//				uint8_t STATUS_1;
//				uint8_t STATUS_2;
//			} BYTES;
//		} ENCODER_1;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t POS_LSB;
//				uint8_t POS_MLB;
//				uint8_t POS_MHB;
//				uint8_t POS_MSB;
//				uint8_t SPEED_LSB;
//				uint8_t SPEED_HSB;
//				uint8_t STATUS_1;
//				uint8_t STATUS_2;
//			} BYTES;
//		} ENCODER_2;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t POS_LSB;
//				uint8_t POS_MLB;
//				uint8_t POS_MHB;
//				uint8_t POS_MSB;
//				uint8_t SPEED_LSB;
//				uint8_t SPEED_HSB;
//				uint8_t STATUS_1;
//				uint8_t STATUS_2;
//			} BYTES;
//		} ENCODER_3;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t POS_LSB;
//				uint8_t POS_MLB;
//				uint8_t POS_MHB;
//				uint8_t POS_MSB;
//				uint8_t SPEED_LSB;
//				uint8_t SPEED_HSB;
//				uint8_t STATUS_1;
//				uint8_t STATUS_2;
//			} BYTES;
//		} ENCODER_4;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t POS_LSB;
//				uint8_t POS_MLB;
//				uint8_t POS_MHB;
//				uint8_t POS_MSB;
//				uint8_t SPEED_LSB;
//				uint8_t SPEED_HSB;
//				uint8_t STATUS_1;
//				uint8_t STATUS_2;
//			} BYTES;
//		} ENCODER_5;
//
//		union {
//			uint8_t ALL[8];
//			struct {
//				uint8_t RES_1;
//				uint8_t RES_2;
//				uint8_t RES_3;
//				uint8_t RES_4;
//				uint8_t RES_5;
//				uint8_t RES_6;
//				uint8_t RES_7;
//				uint8_t RES_8;
//			} BYTES;
//		} ENCODER_6;
//	} DATA;
//
//} ZMV_CAN_FRAME_Rx_U;


#endif /* COMMON_TYPEDEFS_H_ */
