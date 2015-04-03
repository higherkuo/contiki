DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

TARGETDIRS += ../../../atum/contiki/platform

all: udp-server udp-client

CFLAGS += -DRESOLV_CONF_SUPPORTS_MDNS=1
CFLAGS += -DRESOLV_CONF_SUPPORTS_DNS_SD=1
# CFLAGS += -fsanitize=address
# LDFLAGS += -fsanitize=address

CONTIKI = ../..
CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include
