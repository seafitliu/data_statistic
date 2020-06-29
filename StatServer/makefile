#-----------------------------------------------------------------------

APP       := DST
TARGET    := StatisticServer
MFLAGS    :=
DFLAGS    :=
CFLAGS    += -std=c++11 -g -O2 -Wno-deprecated -Wall
CONFIG    :=
STRIP_FLAG:= N
J2CPP_FLAG:= 

LIB_64    += 

INCLUDE   += -I./  -I./thirdlib/wbl/include -I./include \
			 -I./thirdlib/yaml-cpp/include \
             -I./thirdlib/json-cpp/include \
             -I./thirdlib/cctz/include
			 

LIB       += -L./thirdlib/wbl/lib -lwblmysql -L./lib \
             -lpthread -lz -lrt \
             -L/usr/local/mysql/lib/mysql -lmysqlclient \
             -L./thirdlib/yaml-cpp/lib -lyaml-cpp \
             -L./thirdlib/json-cpp/lib -ljsoncpp \
             -L./thirdlib/cctz/lib -lcctz

LOCAL_DIR += ./

LOCAL_SRC += $(foreach dir, $(LOCAL_DIR), $(wildcard $(dir)/*.cpp $(dir)/*.cc ./*.cc))

#-----------------------------------------------------------------------
include /usr/local/tars/cpp/makefile/makefile.tars
