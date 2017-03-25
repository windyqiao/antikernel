/***********************************************************************************************************************
*                                                                                                                      *
* ANTIKERNEL v0.1                                                                                                      *
*                                                                                                                      *
* Copyright (c) 2012-2017 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Implementation of JTAGNOCBridgeInterface
 */
#include "nocbridge.h"
#include "JtagDebugBridge_addresses_enum.h"

using namespace std;

/*
	Generated by the following code snippet (for the ATM HEC polynomial, x^8 + x^2 + x + 1)

	const int poly = 0x107;
	for(int i=0; i<256; i++)
	{
		unsigned int temp = i;
		for(int j=0; j<8; j++)
			temp = (temp << 1) ^ ( (temp & 0x80) ? poly : 0 );
		printf("0x%02x, ", temp & 0xff);
		if( (i & 15) == 15)
			printf("\n");
	}
*/
static const uint8_t g_crc8Table[256] =
{
	//*0    *1    *2    *3    *4    *5    *6    *7    *8    *9    *a    *b    *c    *d    *e    *f
	0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,	//0*
	0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,	//1*
	0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,	//2*
	0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,	//3*
	0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,	//4*
	0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,	//5*
	0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,	//6*
	0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,	//7*
	0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,	//8*
	0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,	//9*
	0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,	//a*
	0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,	//b*
	0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,	//c*
	0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,	//d*
	0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,	//e*
	0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3	//f*
};

/*
	CRC32 code derived from work by Gary S. Brown.

	Original license:
	COPYRIGHT (C) 1986 Gary S. Brown.  You may use this program, or
	code or tables extracted from it, as desired without restriction.
 */
static uint32_t g_crc32Table[] =
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction / destruction

JTAGNOCBridgeInterface::JTAGNOCBridgeInterface(JtagFPGA* pfpga)
	: m_fpga(pfpga)
{
	//Populate free list
	for(unsigned int i = DEBUG_LOW_ADDR; i <= DEBUG_HIGH_ADDR; i++)
		m_freeAddresses.emplace(i);

	//Reset the TAP of our DUT and select USER2 (the actual transfer instruction)
	LogTrace("Initializing JTAG port\n");
	pfpga->ResetToIdle();
	pfpga->SelectUserInstruction(1);

	//Switch to SHIFT-DR but don't send any data
	pfpga->EnterShiftDR();

	//Start out sending packets with a zero sequence number
	m_nextSequence = 0;

	//Not ACKing anything yet
	m_acking = 0;
	m_nextAck = 0;
}

JTAGNOCBridgeInterface::~JTAGNOCBridgeInterface()
{
	m_fpga->ResetToIdle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Address allocation

bool JTAGNOCBridgeInterface::AllocateClientAddress(uint16_t& addr)
{
	//Pop free list, if we have anything there
	if(m_freeAddresses.empty())
		return false;

	addr = *m_freeAddresses.begin();
	m_freeAddresses.erase(addr);

	return true;
}

void JTAGNOCBridgeInterface::FreeClientAddress(uint16_t addr)
{
	//Disable "comparison is always false due to limited range of data type" warnings for here
	//If DEBUG_*_ADDR are at the low/high ends of the address range some comparisons are pointless
	//but we need them there to keep the code generic.
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtype-limits"

	//Warn if we try to do something stupid
	if( (addr < DEBUG_LOW_ADDR) || (addr > DEBUG_HIGH_ADDR) )
	{
		LogWarning("JTAGNOCBridgeInterface: Attempted to free client address %04x, which isn't in the debug subnet\n",
			addr);
		return;
	}

	#pragma GCC diagnostic pop

	//If it's already free, something is funky
	if(m_freeAddresses.find(addr) != m_freeAddresses.end())
	{
		LogWarning("JTAGNOCBridgeInterface: Attempted to free client address %04x, which was already free\n",
			addr);
		return;
	}

	//Nope, we're good
	m_freeAddresses.emplace(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The actual JTAG bridge stuff

/**
	@brief Cycle the JTAG interface with more data

	Push any pending messages to the DUT; send idles if we have nothing to send.
	Take any returned data and put it in our queue.
 */
void JTAGNOCBridgeInterface::Cycle()
{
	//Send up to 4KB (1K words) of data.
	//Note that some of this may be idle frames rather than actual data if there's nothing to send
	//const int tx_buf_len = 1024;

	//Shrink window size for testing
	const int tx_buf_len = 32;

	//TODO: we do NOT want to clear these buffers! Make them member variables and process stuff statefully
	//so that messages can span multiple Cycle() calls

	//Generate an idle frame we can fill empty space in the TX buffer with
	//TODO: Send different data once link is up!
	AntikernelJTAGFrameHeader idle_frame;
	idle_frame.bits.ack = m_acking;				//Might be ACKing packets
	idle_frame.bits.nak = 0;					//not nacking anything
	idle_frame.bits.credits = 0x3FF;			//we have no limit on buffer space, always report "max"
	idle_frame.bits.ack_seq = m_nextAck;		//ACK number
	idle_frame.bits.payload_present = 0;		//no payload
	idle_frame.bits.rpc = 0;					//no RPC payload
	idle_frame.bits.dma = 0;					//no DMA payload
	idle_frame.bits.length = 0;					//empty payload
	idle_frame.bits.reserved_zero = 0;			//nothing here

	//TODO: Send actual messages here

	//TODO: retransmit logic etc

	//Pad the buffer out to size with idle frames
	LogTrace("Sending stuff...\n");
	while(m_txBuffer.size() <= (tx_buf_len - 2) )
	{
		//Sequence number changes for each packet
		idle_frame.bits.sequence = m_nextSequence;	//Sequence number of the outbound packet
		m_nextSequence = NextSeq(m_nextSequence);

		//TODO: Send proper NAKs:
		//One NAK with sequence number of the bad packet
		//then ACK with sequence number of the last good packet (if any)

		//Update the CRC for the new headers
		ComputeHeaderChecksum(idle_frame);

		//Save packet
		m_txBuffer.push_back(idle_frame.words[0]);
		m_txBuffer.push_back(idle_frame.words[1]);

		//only print first few
		if(m_txBuffer.size() < 64)
			PrintMessageHeader(idle_frame);

		//DEBUG: Send an RPC message after the first few idles
		if(m_txBuffer.size() == 8)
		{
			//Send a single RPC message
			AntikernelJTAGFrameHeader rpc_frame;
			rpc_frame.bits.ack = m_acking;
			rpc_frame.bits.nak = 0;
			rpc_frame.bits.credits = 0x3ff;
			rpc_frame.bits.ack_seq = m_nextAck;
			rpc_frame.bits.payload_present = 1;
			rpc_frame.bits.rpc = 1;
			rpc_frame.bits.dma = 0;
			rpc_frame.bits.length = 4;
			rpc_frame.bits.reserved_zero = 0;
			rpc_frame.bits.sequence = m_nextSequence;		//Sequence number of the outbound packet
			m_nextSequence = NextSeq(m_nextSequence);
			ComputeHeaderChecksum(rpc_frame);
			PrintMessageHeader(rpc_frame);
			m_txBuffer.push_back(rpc_frame.words[0]);		//header
			m_txBuffer.push_back(rpc_frame.words[1]);

			vector<uint32_t> payload;						//message body
			payload.push_back(0x11111111);
			payload.push_back(0x22222222);
			payload.push_back(0x33333333);
			payload.push_back(0x44444444);
			for(auto p : payload)
				m_txBuffer.push_back(p);

			m_txBuffer.push_back(
				CRC32(&payload[0], payload.size()*4));	//crc32 of data
		}
	}

	//Input/output data buffers (must be contiguous memory!)
	vector<uint32_t> tx_buf;
	vector<uint32_t> rx_buf;
	tx_buf.reserve(m_txBuffer.size());
	rx_buf.resize(m_txBuffer.size());

	//Append our pending outbox data
	for(auto b : m_txBuffer)
		tx_buf.push_back(b);
	m_txBuffer.clear();

	//Send the actual data
	//TODO: do split transactions
	m_fpga->ShiftData((unsigned char*)&tx_buf[0], (unsigned char*)&rx_buf[0], tx_buf.size() * 32);

	//Append the new data to our existing RX buffer
	for(auto b : rx_buf)
		m_rxBuffer.push_back(b);

	//Process the RX buffer
	LogTrace("Got %d words (%d)\n", (int)rx_buf.size(), (int)m_rxBuffer.size());
	int i = 0;
	while(m_rxBuffer.size() > 1)
	{
		AntikernelJTAGFrameHeader msg;
		msg.words[0] = *m_rxBuffer.begin();
		m_rxBuffer.pop_front();
		msg.words[1] = *m_rxBuffer.begin();
		m_rxBuffer.pop_front();

		//TODO: We need to reset link if this happens, handle it properly!
		if(!VerifyHeaderChecksum(msg))
		{
			LogError("Bad header CRC (at offset %d in buffer)\n", i);
			//break;
		}

		//debug print
		if(i++ < 63)
			PrintMessageHeader(msg);

		//Process payload, if we have it
		if(msg.bits.payload_present)
		{
			//Do we have the full payload?
			//If not, push the headers back onto the start of the buffer and stop.
			if(m_rxBuffer.size() < msg.bits.length)
			{
				LogTrace("Need moar payload\n");
				m_rxBuffer.push_front(msg.words[1]);
				m_rxBuffer.push_front(msg.words[0]);
				break;
			}

			//We have the payload, crunch it
			//For now throw it away
			//TODO: CRC it and do something useful
			for(int i=0; i<msg.bits.length; i++)
			{
				LogTrace("%08x\n", *m_rxBuffer.begin());
				m_rxBuffer.pop_front();
			}
		}

		//If we get here the message was properly verified!
		//Bump the ACK number
		m_acking = true;
		m_nextAck = msg.bits.sequence;
	}
}

/**
	@brief Print out a message
 */
void JTAGNOCBridgeInterface::PrintMessageHeader(const AntikernelJTAGFrameHeader& header)
{
	LogTrace("    %08x %08x: ack = %d, nak = %d, seq = %d, nack = %d, credits=%d, payload = %d, len=%d\n",
		header.words[0],
		header.words[1],
		header.bits.ack,
		header.bits.nak,
		header.bits.sequence,
		header.bits.ack_seq,
		header.bits.credits,
		header.bits.payload_present,
		header.bits.length
		);
}

/**
	@brief Calculate the header CRC for an outbound packet
 */
void JTAGNOCBridgeInterface::ComputeHeaderChecksum(AntikernelJTAGFrameHeader& header)
{
	header.bits.header_checksum = CRC8(header.words, 7);
}

/**
	@brief Make sure an inbound packet has a good header CRC
 */
bool JTAGNOCBridgeInterface::VerifyHeaderChecksum(AntikernelJTAGFrameHeader header)
{
	uint8_t expected = CRC8(header.words, 7);
	uint8_t actual = header.bits.header_checksum;
	bool ok = (expected == actual);
	if(!ok)
		LogTrace("expected: %02x, actual: %02x\n", expected, actual);
	return ok;
}

/**
	@brief Checksums a buffer of data in network byte order

	//TODO: switch to faster implementation? this is slooow
 */
uint8_t JTAGNOCBridgeInterface::CRC8(uint32_t* data, unsigned int len)
{
	uint8_t crc = 0x00;
	for(unsigned int i=0; i<len; i += 4)
	{
		uint32_t d = data[i/4];
		for(unsigned int j=i; j < len && j < (i+4); j++)
		{
			uint8_t b = (d >> 24) & 0xff;
			crc = g_crc8Table[crc ^ b];
			d <<= 8;
		}
	}
	return crc;
}

uint32_t JTAGNOCBridgeInterface::CRC32(uint32_t* data, unsigned int len)
{
	uint32_t crc = 0xffffffff;

	for(unsigned int i=0; i<len; i += 4)
	{
		uint32_t d = data[i/4];
		for(unsigned int j=i; j < len && j < (i+4); j++)
		{
			uint8_t b = (d >> 24) & 0xff;
			crc = g_crc32Table[ (crc ^ b) & 0xff] ^ (crc >> 8);
			d <<= 8;
		}
	}
	return ~crc;
}
