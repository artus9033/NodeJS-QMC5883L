HDRS = I2Cdev.h MechaQMC5883.h 
CMN_OBJS = I2Cdev.o MechaQMC5883.o

CXXFLAGS = -Wall -g -O2 `pkg-config gtkmm-3.0 --cflags --libs`

$(CMN_OBJS) : $(HDRS)

clean:
	rm -f $(CMN_OBJS) $(RAW_OBJS)

