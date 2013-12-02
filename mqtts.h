#ifndef MQTT_SN_H
#define MQTT_SN_H

#ifndef FALSE
#define FALSE  (0)
#endif

#ifndef TRUE
#define TRUE  (1)
#endif


#define MQTT_SN_MAX_PACKET_LENGTH  (256)

#define MQTT_SN_TYPE_ADVERTISE     (0x00)
#define MQTT_SN_TYPE_SEARCHGW      (0x01)
#define MQTT_SN_TYPE_GWINFO        (0x02)
#define MQTT_SN_TYPE_CONNECT       (0x04)
#define MQTT_SN_TYPE_CONNACK       (0x05)
#define MQTT_SN_TYPE_WILLTOPICREQ  (0x06)
#define MQTT_SN_TYPE_WILLTOPIC     (0x07)
#define MQTT_SN_TYPE_WILLMSGREQ    (0x08)
#define MQTT_SN_TYPE_WILLMSG       (0x09)
#define MQTT_SN_TYPE_REGISTER      (0x0A)
#define MQTT_SN_TYPE_REGACK        (0x0B)
#define MQTT_SN_TYPE_PUBLISH       (0x0C)
#define MQTT_SN_TYPE_PUBACK        (0x0D)
#define MQTT_SN_TYPE_PUBCOMP       (0x0E)
#define MQTT_SN_TYPE_PUBREC        (0x0F)
#define MQTT_SN_TYPE_PUBREL        (0x10)
#define MQTT_SN_TYPE_SUBSCRIBE     (0x12)
#define MQTT_SN_TYPE_SUBACK        (0x13)
#define MQTT_SN_TYPE_UNSUBSCRIBE   (0x14)
#define MQTT_SN_TYPE_UNSUBACK      (0x15)
#define MQTT_SN_TYPE_PINGREQ       (0x16)
#define MQTT_SN_TYPE_PINGRESP      (0x17)
#define MQTT_SN_TYPE_DISCONNECT    (0x18)
#define MQTT_SN_TYPE_WILLTOPICUPD  (0x1A)
#define MQTT_SN_TYPE_WILLTOPICRESP (0x1B)
#define MQTT_SN_TYPE_WILLMSGUPD    (0x1C)
#define MQTT_SN_TYPE_WILLMSGRESP   (0x1D)

#define MQTT_SN_TOPIC_TYPE_NORMAL     (0x00)
#define MQTT_SN_TOPIC_TYPE_PREDEFINED (0x01)
#define MQTT_SN_TOPIC_TYPE_SHORT      (0x02)


#define MQTT_SN_FLAG_DUP     (0x1 << 7)
#define MQTT_SN_FLAG_QOS_0   (0x0 << 5)
#define MQTT_SN_FLAG_QOS_1   (0x1 << 5)
#define MQTT_SN_FLAG_QOS_2   (0x2 << 5)
#define MQTT_SN_FLAG_QOS_N1  (0x3 << 5)
#define MQTT_SN_FLAG_RETAIN  (0x1 << 4)
#define MQTT_SN_FLAG_WILL    (0x1 << 3)
#define MQTT_SN_FLAG_CLEAN   (0x1 << 2)

#define MQTT_SN_PROTOCOL_ID  (0x01)

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t flags;
  uint8_t protocol_id;
  uint16_t duration;
  char client_id[21];
} connect_packet_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint8_t return_code;
} connack_packet_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint16_t topic_id;
  uint16_t message_id;
  char topic_name[MQTT_SN_MAX_PACKET_LENGTH-6];
} register_packet_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint16_t topic_id;
  uint16_t message_id;
  uint8_t return_code;
} regack_packet_t;

typedef struct __attribute__((packed)) {
  uint8_t length;
  uint8_t type;
  uint8_t flags;
  uint16_t topic_id;
  uint16_t message_id;
  char data[MQTT_SN_MAX_PACKET_LENGTH-7];
} publish_packet_t;

typedef struct __attribute__((packed)) {
  uint8_t length;
  uint8_t type;
  uint8_t flags;
  uint16_t message_id;
  char topic_name[MQTT_SN_MAX_PACKET_LENGTH-5];
} subscribe_packet_t;

typedef struct __attribute__((packed)) {
  uint8_t length;
  uint8_t type;
  uint8_t flags;
  uint16_t topic_id;
  uint16_t message_id;
  uint8_t return_code;
} suback_packet_t;

typedef struct {
  uint8_t length;
  uint8_t type;
  uint16_t duration;
} disconnect_packet_t;


// Library functions
int mqtt_sn_create_socket(const char* host, const char* port);
void mqtt_sn_send_connect(int sock, const char* client_id, uint16_t keepalive);
void mqtt_sn_send_register(int sock, const char* topic_name);
void mqtt_sn_send_publish(int sock, uint16_t topic_id, uint8_t topic_type, const char* data, int8_t qos, uint8_t retain);
void mqtt_sn_send_subscribe(int sock, const char* topic_name, uint8_t qos);
void mqtt_sn_send_pingreq(int sock);
void mqtt_sn_send_disconnect(int sock);
void mqtt_sn_recieve_connack(int sock);
uint16_t mqtt_sn_recieve_regack(int sock);
uint16_t mqtt_sn_recieve_suback(int sock);
publish_packet_t* mqtt_sn_loop(int sock, int timeout);

void mqtt_sn_set_debug(uint8_t value);
const char* mqtt_sn_type_string(uint8_t type);
const char* mqtt_sn_return_code_string(uint8_t return_code);

#endif
