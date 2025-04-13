// -----------------------------------------------------------------------------------
// IP communication routines

// original work by jesco-t

#include "Serial_IP_Wifi_Client.h"

#if OPERATIONAL_MODE == WIFI && SERIAL_CLIENT == ON

  bool IPSerialClient::begin(long port, unsigned long clientTimeoutMs, bool persist) { 
    if (active) return true;

    // special case where the port is the most common baud rate
    // so a standard call to begin(baud_rate) can still work
    if ((port < 9000 || port >= 10000 || port == 9600) && clientTimeoutMs == 2000 && persist == false) port = 9996;

    this->port = port;
    this->clientTimeoutMs = clientTimeoutMs;
    this->persist = persist;

    if (!wifiManager.init()) {
      DLF("WRN: IPSerialClient, failed to start WiFi");
      return false;
    }

    delay(1000);

    onStep = IPAddress(wifiManager.sta->target);
    if (!cmdSvrClient.connect(onStep, port)) {
      DLF("WRN: IPSerialClient, connection to target failed");
      return false;
    }

    VF("MSG: IPSerialClient, connected to "); V(onStep.toString()); V(":"); VL(port);
    active = true;

    return true;
  }

  void IPSerialClient::end() {
    if (!active) return;
    
    cmdSvrClient.stop();
    VLF("MSG: IPSerialClient, connection to target closed");
    WiFi.disconnect();
    VLF("MSG: IPSerialClient, WiFi disconnected");
    active = false;
  }

  bool IPSerialClient::isConnected() {
    if (WiFi.status() == WL_CONNECTED) {
      if (!cmdSvrClient.connected()) {
        if (cmdSvrClient.connect(onStep, port)) {
          VLF("MSG: IPSerialClient, connection to target restarted");
          return true;
        } else {
          DLF("WRN: IPSerialClient, connection to target failed");
          return false;
        }
      } else return true;
    } else { active = false; return false; }
  }

  void IPSerialClient::flush(void) {
    if (!active || !isConnected()) return;

    return cmdSvrClient.flush();
  }

  int IPSerialClient::available(void) {
    if (!active || !isConnected()) return 0;

    return cmdSvrClient.available();
  }

  int IPSerialClient::peek(void) {
    if (!active || !isConnected()) return -1;

    return cmdSvrClient.peek();
  }

  int IPSerialClient::read(void) {
    if (!active || !isConnected()) return -1;

    return cmdSvrClient.read();
  }

  size_t IPSerialClient::write(uint8_t data) {
    if (!active || !isConnected()) return 0;

    return cmdSvrClient.write(data);
  }

  size_t IPSerialClient::write(const uint8_t *data, size_t quantity) {
    if (!active || !isConnected()) return 0;

    return cmdSvrClient.write(data, quantity);
  }

  IPSerialClient SerialIPClient;
#endif
