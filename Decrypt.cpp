#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


std::string decryptKey(){
  	int8_t indx = 15;
	std::stringstream keyStream;

  	// Array to store out encrypted AES key
  	uint16_t encrypted_Key[] = {0x95, 0xB3, 0x15, 0x32, 
				    0xE4, 0xE4, 0x43, 0x6B, 
				    0x90, 0xBE, 0x1B, 0x31, 
				    0xA7, 0x8B, 0x2D, 0x5};	

	// Xor indexes by the hardcoded values
	while(indx > 0){
		encrypted_Key[indx] ^= 0x5;
		encrypted_Key[indx-1] ^= 0x2D;
		encrypted_Key[indx-2] ^= 0x8B;
		encrypted_Key[indx-3] ^= 0xA7;
		indx -= 4;
	}
	
  	// parse the decrypted key as hex into the keystream
	for(int8_t v = 0; v < 15; v++){
		keyStream << std::hex << encrypted_Key[v];
	}

  	// store the parsed decrypted key as a string for return 
	std::string decryptedKey(keyStream.str());
	
	return decryptedKey;
}

int main(int argc, const char* argv[]){
	
	if(argc != 2){
		std::cout << "Supply only the firmware" << std::endl;
		return -1;
	}

	/* lol, so this will be more useful when i add support for other firmware imgs */
	if((std::string)argv[1] == "--help"){
		std::cout << "./plcDecrypt [FIRMWARE_IMAGE]" << std::endl;
		return 0;
	}

	// We will now check if the supplied firmware file exists on the system
	std::filesystem::path firmwarePath = argv[1];
	std::filesystem::directory_entry firmwareEntry{firmwarePath};

	// Supplied firmware does not exist
	if(!firmwareEntry.exists()){
		std::cout << "Unable to locate firmware" << std::endl;
		return -1;
	}

	// Now we will take the firmware image provided and truncate it by 40 bytes This is required per the dec routine within the upgrade binary
	rename(argv[1], "fw.rom"); // renaming this, so that we can pass it to DD without supplying user input to system(), horrible idea
	system("dd if=fw.rom of=dMe.rom bs=1 skip=40");

	// Lastly we will pass the decrypted AES KEY to openssl to decrypt the firmware..
	std::string dCmd = "openssl aes-128-ecb -d -K ";
	dCmd.append(decryptKey());
	dCmd.append(" -in dMe.rom -out final.rom");
	system(dCmd.c_str());

	// We will extract contents from the decrypted firmware and then clean up
	system("binwalk -e final.rom");
	system("rm -rf dMe.rom final.rom");

	return 0;

}
