


#ifndef PACKETCONTROLLER_H
#define PACKETCONTROLLER_H

#include <QThread>						//Base of DivertController

#include <Ws2tcpip.h>					//Types used with WinDivert when handling packets
#include <Iphlpapi.h>					//Types used with WinDivert & functions to obtain the IP Address from MAC Address
#include <mmsystem.h>					//Time APIs used during synchronization

#include <InssidiousCore/TamperModules/TamperBase.h>
#include <InssidiousCore/TamperTypes.h>

class DivertController : public QThread
{
	Q_OBJECT


public:
	DivertController(device* d);	

	void createThreads();


signals:
	void divertStopped(QString MACAddress);

public slots:
	void onDivertStop();

private:
	
	/* QThread class calls run as the first thing executed as the new thread */
	/* Do initialization work like identifying IP address here and opening WinDivert handle */

	void run();


	/* Pointer to the device instance with states and device info */

	device* parentDevice;


	/* PacketList to hold all diverted packets, TamperModule* to individual tamper classes */

	PacketList* packetList;
	TamperModule* tamperModule[NUM_TAMPER_TYPES];


	/* Handles to the WinDivert instance, the two threads, and the synchronization mutex */

	HANDLE divertHandle, loopThread, clockThread, mutex;
	QString inboundFilterString;
	QString outboundFilterString;


	/* Functions to create threads to process packets captured by WinDivert */
	/* Static functions to pass to CreateThread that fire the instance-specific function */

	static DWORD StaticReadLoopThreadStart(void* pDivertControllerInstance);
	static DWORD StaticClockLoopThreadStart(void* pDivertControllerInstance);
	DWORD divertReadLoop();
	DWORD divertClockLoop();


	// step function to let module process and consume all packets on the list
	void divertConsumeStep();


	// sends all packets on the list
	int sendAllListPackets();

};

#endif // PACKETCONTROLLER_H
