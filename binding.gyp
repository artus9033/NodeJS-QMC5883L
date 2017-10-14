{
	"targets": [
		{
			"target_name": "binding",
			"sources": [ "src/binding.cc", "src/I2Cdev.cpp", "src/MechaQMC5883.cpp" ],
			#"defines": ["SOME_FLAG=1"],
			"cflags": [ "-std=c++11" ]
		}
	]
}
