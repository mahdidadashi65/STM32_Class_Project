#include "main.h"
#include "mb.h"
#include "mbport.h"



#define REG_INPUT_START       0
#define REG_INPUT_NREGS       300

#define REG_COILS_START       0
#define REG_COILS_SIZE        8

#define REG_HOLDING_START     0
#define REG_HOLDING_SIZE      300

#define REG_DISCRETE_START    1
#define REG_DISC_SIZE         16

static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS];

unsigned char ucRegCoilsBuf[REG_COILS_SIZE / 8];
int16_t ucRegHoldingBuf[REG_HOLDING_SIZE];
unsigned char ucRegDiscBuf[REG_DISC_SIZE / 8];


void ModbusRTUTask(void const * argument)
{ 
  /* ABCDEF */
  usRegInputBuf[0] = 11;
  usRegInputBuf[1] = 22;
  usRegInputBuf[2] = 33;
  usRegInputBuf[3] = 44;
  usRegInputBuf[4] = 55;
  usRegInputBuf[5] = 66;
  usRegInputBuf[6] = 77;
  usRegInputBuf[7] = 88;  
  
  eMBErrorCode eStatus = eMBInit( MB_RTU, 6, 3, 19200, MB_PAR_NONE );
  eStatus = eMBEnable();
  
  uint16_t adc;
  while(1) 
  {
    adc++;
    usRegInputBuf[0] = adc;
    eMBPoll();           
  }
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
				
//				HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
    }
    else
    {
	//		  HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
        eStatus = MB_ENOREG;			
    }

    return eStatus;
}


void UpdateHoldingRegisters(USHORT usAddress,USHORT usNRegs, eMBRegisterMode eMode)
{
//	uint16_t tmp;
//	float  tmpf;
//	int HoldBufLoc=0;
//	if(eMode==MB_REG_READ)
//	{
//		
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.Counter1S;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.MyStatus;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DigitalOUT;		
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.RTempSetPoint;		
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.ROnOff;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.RFanMode;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.RFanSpeed;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.RWindMode;
//				
//	    ucRegHoldingBuf[HoldBufLoc++]=MyData.MBMaster_Baud;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.MBMaster_Config;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.MBSalve_Baud;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.MBSlave_Config;

//		for(int i=0;i<4;i++)
//		{
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.AIN[i].Type;
//		    ucRegHoldingBuf[HoldBufLoc++]=MyData.AIN[i].A*10.0f;
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.AIN[i].B*10.0f;
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.AIN[i].Setpoint*10.0f;
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.AIN[i].Val*10.0f;
//		}
//		
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DS18Count;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DS18Learn;
////		for(int i=0;i<MaxDS18Count;i++)
////		{
////			ucRegHoldingBuf[HoldBufLoc++]=MyData.DS18Temp[i];		
////		}
////		for(int i=0;i<MaxDS18Count;i++)
////		{
////			for(int n=0;n<8;n++)
////			{
////				ucRegHoldingBuf[HoldBufLoc++]=MyData.DS18ID[i][n];
////			}
////		}
//				
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperEn;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperSpeed;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperCountL1;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperCountR1;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperCountL2;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.StepperCountR2;
//		
//		
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Second;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Minute;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Hour;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Day;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Month;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.Year;
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.DateTime.WeekDay;
//	
//			
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.WIFI_Config;// ap or station
//		ucRegHoldingBuf[HoldBufLoc++]=MyData.MyPort;
//		for(int i=0;i<4;i++)
//		{
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.MyIP[i];		
//		}
//		
//		for(int i=0;i<20;i++)
//		{
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.APName[i];		
//		}
//		
//		for(int i=0;i<20;i++)
//		{
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.APPass[i];		
//		}
//		
//		
//	 ucRegHoldingBuf[HoldBufLoc++]=MyData.AutoStartEn;
//		for(int i=0;i<7;i++)
//		{
//		   ucRegHoldingBuf[HoldBufLoc++]=MyData.StartTime[i] ;
//           ucRegHoldingBuf[HoldBufLoc++]=MyData.StopTime[i];			
//		}
//		
//		
////		printf("S_DigitalOUT %d\r\n",HoldBufLoc);
//		for(int i=0;i<16;i++)
//		{
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.S_DigitalOUT[i];	
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.S_MyStatus[i];
//			ucRegHoldingBuf[HoldBufLoc++]=MyData.S_RTempSetPoint[i];
//					
//		}		
//		
//		
//		//printf("HoldBufLoc %d\r\n",HoldBufLoc);
//	}
//	else
//	{
//		printf("Wcfg: %d  %d  %d\r\n",usAddress,usNRegs,ucRegHoldingBuf[usAddress+usNRegs]);
//		HoldBufLoc=0;
//		MyData.Counter1S=ucRegHoldingBuf[HoldBufLoc++];		
//		MyData.MyStatus=ucRegHoldingBuf[HoldBufLoc++];
//		
//		if(MyData.MyMode==Mode_Manual)
//		{
//			tmp=MyData.DigitalOUT;
//			MyData.DigitalOUT=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.DigitalOUT)
//			{
//				Config_writeEEPROM2(MyData.DigitalOUT,R_DigitalOUT);
//			}
//		}
//		else
//		{
//			tmp=ucRegHoldingBuf[HoldBufLoc++];
//		}
//		//printf("MyMode %d DigitalOUT %d\r\n",MyData.MyMode,MyData.DigitalOUT);
//		
//		
//		    tmp=MyData.RTempSetPoint;
//			MyData.RTempSetPoint=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.RTempSetPoint)
//			{
//				Config_writeEEPROM2(MyData.RTempSetPoint,R_TempSetPoint);
//			}
//		    
//			
//			tmp=MyData.ROnOff;
//			MyData.ROnOff=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.ROnOff)
//			{
//			Config_writeEEPROM2(MyData.ROnOff,R_ROnOff);
//			}

//			tmp=MyData.RFanMode;
//			MyData.RFanMode=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.RFanMode)
//			{
//			Config_writeEEPROM2(MyData.RFanMode,R_RFanMode);
//			}
//			tmp=MyData.RFanSpeed;
//			MyData.RFanSpeed=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.RFanSpeed)
//			{
//			Config_writeEEPROM2(MyData.RFanSpeed,R_RFanSpeed);
//			}
//			tmp=MyData.RWindMode;
//			MyData.RWindMode=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.RWindMode)
//			{
//			Config_writeEEPROM2(MyData.RWindMode,R_RWindMode);
//			}
//			tmp=MyData.MBMaster_Baud;
//			MyData.MBMaster_Baud=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MBMaster_Baud)
//			{
//			Config_writeEEPROM2(MyData.MBMaster_Baud,R_MBMaster_Baud);
//			}
//			tmp=MyData.MBMaster_Config;
//			MyData.MBMaster_Config=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MBMaster_Config)
//			{
//			Config_writeEEPROM2(MyData.MBMaster_Config,R_MBMaster_Config);
//			}
//			tmp=MyData.MBSalve_Baud;
//			MyData.MBSalve_Baud=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MBSalve_Baud)
//			{
//			Config_writeEEPROM2(MyData.MBSalve_Baud,R_MBSalve_Baud);
//			}
//			
//			tmp=MyData.MBSlave_Config;
//			MyData.MBSlave_Config=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MBSlave_Config)
//			{
//			Config_writeEEPROM2(MyData.MBSlave_Config,R_MBSlave_Config);
//			}
//	
//			int L;
//		for(int i=0,L=0;i<4;i++,L+=8)
//		{
//		
//			tmp=MyData.AIN[i].Type;
//			MyData.AIN[i].Type=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.AIN[i].Type)
//			{
//				Config_writeEEPROM2(MyData.AIN[i].Type,R_AINType0+L);
//			}
//						
//			tmpf=MyData.AIN[i].A;
//			MyData.AIN[i].A=ucRegHoldingBuf[HoldBufLoc++]/10.0f;
//			if(tmpf!=MyData.AIN[i].A)
//			{
//			Config_writeEEPROM2(MyData.AIN[i].A*10.0f,R_AINA0+L);
//				printf("A %d %f\r\n",i,MyData.AIN[i].A);
//			}
//			
//			
//			tmpf=MyData.AIN[i].B;
//			MyData.AIN[i].B=ucRegHoldingBuf[HoldBufLoc++]/10.0f;
//			if(tmpf!=MyData.AIN[i].B)
//			{
//			Config_writeEEPROM2(MyData.AIN[i].B*10,R_AINB0+L);
//				printf("B %d %f\r\n",i,MyData.AIN[i].B);
//			}
//						
//			tmpf=MyData.AIN[i].Setpoint;
//			MyData.AIN[i].Setpoint=ucRegHoldingBuf[HoldBufLoc++]/10.0f;
//			if(tmpf!=MyData.AIN[i].Setpoint)
//			{
//			Config_writeEEPROM2(MyData.AIN[i].Setpoint*10,R_AINSetpoint0+L);
//			}
//			
//			MyData.AIN[i].Val = ucRegHoldingBuf[HoldBufLoc++]/10.0f;
//		}
//		
//		tmp=MyData.DS18Count;
//			MyData.DS18Count=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.DS18Count)
//			{
//			Config_writeEEPROM2(MyData.DS18Count,R_DS18Count);
//			}
//			
//			
//			
//		MyData.DS18Learn = ucRegHoldingBuf[HoldBufLoc++];
////		for(int i=0;i<MaxDS18Count;i++)
////		{
////			MyData.DS18Temp[i]= ucRegHoldingBuf[HoldBufLoc++];		
////		}
////		for(int i=0;i<MaxDS18Count;i++)
////		{
////			for(int n=0;n<8;n++)
////			{
////				MyData.DS18ID[i][n]= ucRegHoldingBuf[HoldBufLoc++];
////			}
////		}
//				
//	
//					tmp=MyData.StepperEn;
//			MyData.StepperEn=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperEn)
//			{
//			Config_writeEEPROM2(MyData.StepperEn,R_StepperEn);
//			}
//			
//	
//				tmp=MyData.StepperSpeed;
//			MyData.StepperSpeed=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperSpeed)
//			{
//			Config_writeEEPROM2(MyData.StepperSpeed,R_StepperSpeed);
//			}
//			
//				tmp=MyData.StepperCountL1;
//			MyData.StepperCountL1=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperCountL1)
//			{
//			Config_writeEEPROM2(MyData.StepperCountL1,R_StepperCountL1);
//			}
//			
//			tmp=MyData.StepperCountR1;
//			MyData.StepperCountR1=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperCountR1)
//			{
//			Config_writeEEPROM2(MyData.StepperCountR1,R_StepperCountR1);
//			}
//			
//							tmp=MyData.StepperCountL2;
//			MyData.StepperCountL2=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperCountL2)
//			{
//			Config_writeEEPROM2(MyData.StepperCountL2,R_StepperCountL2);
//			}
//			
//			tmp=MyData.StepperCountR2;
//			MyData.StepperCountR2=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StepperCountR2)
//			{
//			Config_writeEEPROM2(MyData.StepperCountR2,R_StepperCountR2);
//			}
//			

//		
//		MyData.DateTime.Second = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.Minute = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.Hour = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.Day = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.Month = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.Year = ucRegHoldingBuf[HoldBufLoc++];
//		MyData.DateTime.WeekDay = ucRegHoldingBuf[HoldBufLoc++];
//			
//		if(usAddress>=40&&usAddress<=46)
//		{
//			UpdateRTC(MyData.DateTime);
//		}

//		
//			tmp=MyData.WIFI_Config;
//			MyData.WIFI_Config=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.WIFI_Config)
//			{
//			Config_writeEEPROM2(MyData.WIFI_Config,R_WIFI_Config);
//			}
//			
//		
//			tmp=MyData.MyPort;
//			MyData.MyPort=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MyPort)
//			{
//			Config_writeEEPROM2(MyData.MyPort,R_MyPort);
//			}
//			
//			
//		for(int i=0,L=0;i<4;i++,L+=2)
//		{	
//			tmp=MyData.MyIP[i];
//			MyData.MyIP[i]=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.MyIP[i])
//			{
//			Config_writeEEPROM2(MyData.MyIP[i],R_MyIP0+L);
//			}			
//		}
//		
//		for(int i=0,L=0;i<20;i++,L+=2)
//		{
//			tmp=MyData.APName[i];
//			MyData.APName[i]=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.APName[i])
//			{
//			Config_writeEEPROM2(MyData.APName[i],R_APName0+L);
//			}				
//		}
//		
//		for(int i=0,L=0;i<20;i++,L+=2)
//		{
//			tmp=MyData.APPass[i];
//			MyData.APPass[i]=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.APPass[i])
//			{
//			Config_writeEEPROM2(MyData.APPass[i],R_APPass0+L);
//			}			
//		}	

//		
//					tmp=MyData.AutoStartEn;
//			MyData.AutoStartEn=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.AutoStartEn)
//			{
//			Config_writeEEPROM2(MyData.AutoStartEn,R_AutoStartEn);
//			}
//			
//		for(int i=0, L=0;i<7;i++,L+=4)
//		{


//			tmp=MyData.StartTime[i];
//			MyData.StartTime[i]=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StartTime[i])
//			{
//			Config_writeEEPROM2(MyData.StartTime[i],R_StartTime0+L);
//			}	


//			tmp=MyData.StopTime[i];
//			MyData.StopTime[i]=ucRegHoldingBuf[HoldBufLoc++];
//			if(tmp!=MyData.StopTime[i])
//			{
//			Config_writeEEPROM2(MyData.StopTime[i],R_StopTime0+L);
//			}	
//			
//		}
//		
//		//printf("w S_DigitalOUT %d\r\n",HoldBufLoc);
//		for(int i=0;i<16;i++)
//		{
//			MyData.S_DigitalOUT[i] = ucRegHoldingBuf[HoldBufLoc++];
//			MyData.S_MyStatus[i] = ucRegHoldingBuf[HoldBufLoc++];
//			MyData.S_RTempSetPoint[i] = ucRegHoldingBuf[HoldBufLoc++];						
//		}
//		
//		//printf("w qq Multiple %x %x %x \r\n",MyData.S_DigitalOUT[0],MyData.S_MyStatus[0],MyData.S_RTempSetPoint[0]);
//		MyData.NewHolding=1;
//		//printf("write hold\r\n");
//	}

}


eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress,USHORT usNRegs, eMBRegisterMode eMode)
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex;
    /* it already plus one in modbus function method. */
    usAddress--;

    if ((usAddress >= REG_HOLDING_START)
            && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_SIZE))
    {
        iRegIndex = usAddress - REG_HOLDING_START;
        switch (eMode)
        {
        /* read current register values from the protocol stack. */
        case MB_REG_READ:
			UpdateHoldingRegisters( usAddress, usNRegs,  eMode);
            while (usNRegs > 0)
            {
                *pucRegBuffer++ = (UCHAR) (ucRegHoldingBuf[iRegIndex] >> 8);
                *pucRegBuffer++ = (UCHAR) (ucRegHoldingBuf[iRegIndex] & 0xFF);
                iRegIndex++;
                usNRegs--;
            }
            break;

        /* write current register values with new values from the protocol stack. */
        case MB_REG_WRITE:
            while (usNRegs > 0)
            {
                ucRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                ucRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
			UpdateHoldingRegisters( usAddress, usNRegs,  eMode);
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
		printf("err 1\r\n");
    }
    return eStatus;
}


eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    short           iNDiscrete = ( short )usNDiscrete;
    unsigned short  usBitOffset = 0;

    if( ( usAddress >= REG_DISCRETE_START ) &&
        ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISC_SIZE ) )
    {
        usBitOffset = ( unsigned short )( usAddress - REG_DISCRETE_START );
        while( iNDiscrete > 0 )
        {
            *pucRegBuffer++ =
                xMBUtilGetBits( ucRegDiscBuf, usBitOffset,
                                ( unsigned char )( iNDiscrete >
                                                   8 ? 8 : iNDiscrete ) );
            iNDiscrete -= 8;
            usBitOffset += 8;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}


