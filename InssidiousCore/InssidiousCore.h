#ifndef INSSIDIOUSCORE_H
#define INSSIDIOUSCORE_H

/*
*  File:		inssidiouscore.h
*  Author:		Ian Bannerman
*  License:		GNU Public License v3
*
*  Description:
*
*
*/


#include <QThread>										//Core is a QThread running separately from the Inssidious UI

class HostedNetworkController;
class ICSController;
class DeviceController;
class DHCPController;
enum HostedNetworkReason;
enum TamperType;

class InssidiousCore : public QThread
{
	Q_OBJECT

public:
	InssidiousCore();
	~InssidiousCore();

	QList<QString>* pNetworkConnectionNames;						//Public list of network connection names to share with Startup widget


public slots:
	void onUiCoreStart(QString networkName, QString networkPassword, QString networkAdapter);									
	void onUiTamperStart(QString MACAddress, int tamperType);
	void onUiTamperStop(QString MACAddress, int tamperType);


	void onCoreTamperStarted(QString MACAddress, TamperType tamperType);
	void onCoreTamperStopped(QString MACAddress, TamperType tamperType);

private slots:
	void onCoreHostedNetworkMessage(QString message, HostedNetworkReason reason);								
	void onCoreDHCPipAddressAssigned(QString ipAddress, QString MACAddress);

signals:
	void coreStarting(QString statusMessage, bool error = false);
	void coreStarted();
	void coreStopped();

	void coreAddDevice(QString MACAddress);
	void coreDropDevice(QString MACAddress);
	void coreUpdateDevice(QString MACAddress, QString ipAddress);

	void coreTamperStart(QString MACAddress, TamperType tamperType);
	void coreTamperStop(QString MACAddress, TamperType tamperType);

	void coreTamperStarted(QString MACAddress, TamperType tamperType);
	void coreTamperStopped(QString MACAddress, TamperType tamperType);



private:
	void run() override;											//Calls QThread exec() to start the thread's event loop


	HostedNetworkController* hostedNetwork;	
	ICSController* ics;	
	DeviceController* deviceController;
	DHCPController* dhcpController;
};

#endif // INSSIDIOUSCORE_H
