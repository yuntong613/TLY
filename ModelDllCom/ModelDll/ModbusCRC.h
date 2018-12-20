WORD CalcCRCModBus(BYTE cDataIn, WORD wCRCIn)     
{     
	WORD wCheck = 0;     
	wCRCIn = wCRCIn ^ cDataIn;     

	for(int i = 0; i < 8; i++)     
	{     
		wCheck = wCRCIn & 1;     
		wCRCIn = wCRCIn >> 1;     
		wCRCIn = wCRCIn & 0x7fff;     

		if(wCheck == 1)     
		{     
			wCRCIn = wCRCIn ^ 0xa001;     
		}     
		wCRCIn = wCRCIn & 0xffff;     
	}     

	return wCRCIn;     
}    

void CheckCRCModBus(BYTE* pDataIn, int iLenIn, WORD* pCRCOut)     
{     
	WORD wHi = 0;     
	WORD wLo = 0;     
	WORD wCRC;     
	wCRC = 0xFFFF;     

	for (int i = 0; i < iLenIn; i++)     
	{     
		wCRC = CalcCRCModBus(*pDataIn, wCRC);     
		pDataIn++;     
	}     

	wHi = wCRC % 256;     
	wLo = wCRC / 256;        
	wCRC = (wHi << 8) | wLo;     

	*pCRCOut = wCRC;     
}     