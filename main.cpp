#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Image.h"   
#include "Image.cpp"   // Include the Image header
#include "GSCImage.h"   // Include the GSCImage header
#include "RGBImage.h"   // Include the RGBImage header
#include "GSCImage.cpp"
#include "RGBImage.cpp"
#include "GSCPixel.h"
#include "RGBPixel.h"
#include "GSCPixel.cpp"
#include "RGBPixel.cpp"
#include "Pixel.h"
#include "Pixel.cpp"
#include "Token.h"
#include "Token.cpp"
#include "ImageDatabase.h"
#include "ImageDatabase.cpp"



int main() {
	

	
	
	Image* readNetpbmImage(const char* filename);
	ImageDatabase db;
	std::string inputString;
	
    
    while (true) {
		
        std::cout << "i <filename> as <$token> \n";
        std::cout << "e <$token> as <filename> \n";
        std::cout << "d <$token>\n";
        std::cout << "n <$token>\n";
        std::cout << "z <$token>\n";
        std::cout << "m <$token>\n";
        std::cout << "g <$token>\n";
        std::cout << "s <$token> by <factor>\n";
        std::cout << "q \n";
          
         // std::cout << "////////////////////// \n";
          
          
          
        std::getline(std::cin, inputString);
		std::vector<std::string> words;
		std::istringstream iss(inputString);
		std::string word;

while (std::getline(iss, word, ' ')) {
	 //std::cout << "Debug: Word: " << word << std::endl;
    words.push_back(word);
}

///////////////////////
//for (const auto& w : words) {
//        std::cout << "Debug: Word: " << w << std::endl;
//    }
//////////////////////////////




if (words[0] == "i") {
	//std::cout << "Debug: Import command detectedbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n";
    std::string tokenName = words[3];
    
    //////////////
    //std::cout << "Debug: Token name: " << tokenName << std::endl;
    ///////////
    
    if (words.size() >= 4 && words[2] == "as" && words[3][0] == '$')  {
    	
    
    	
    	
        // Import image
        if (words.size() == 4 && words[2] == "as" && words[3][0] == '$') {
            // Check if token already exists
            if (db.getTokenPosition(tokenName) != -1) {
                std::cout << "[ERROR] Token " << tokenName << " exists\n";
            } else {
                // Import the image and insert into the database
                Image* img = readNetpbmImage(words[1].c_str());
                if (img) {
                    db.insertImage(img, tokenName);
                    std::cout << "[OK] Import " << tokenName << "\n";
                    //std::cout << "Image imported and associated with token " << tokenName << "\n";
                } else {
                    std::cout << "[ERROR] Failed to import image\n";
                }
            }
        }else {
            std::cout << "Invalid command\n";
        }

		//std::cout << "Debug: Import command detectedaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
		
	}
	
	}
	 else if (words[0] == "e") {
	if (words.size() >= 4 && words[2] == "as" && words[1][0] == '$') {
    std::string tokenName = words[1];
    std::string filePath = words[3];
    int tokenPosition = db.getTokenPosition(tokenName);
    if (tokenPosition == -1) {
        std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
    } else {
    Image* img = db.getImage(tokenName); // Use tokenName here

    if (img) {
    	RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
        if (rgbImage) {
                std::ofstream rgbOutputFile(filePath);
                if (rgbOutputFile.is_open()) {
                //	if(std::ifstream(filePath)){
                //		std::cout << "[ERROR] File exists" << std::endl;
				//	}else {
					rgbOutputFile << *rgbImage; // Use the appropriate operator for RGBImage
                    rgbOutputFile.close();
                    std::cout << "[OK] Export "<< tokenName << std::endl;
					//}
                    
                } else {
                    std::cout << "[ERROR] Unable to create file" << std::endl;
                }
            
        } else{
        	GSCImage* gscImg = dynamic_cast<GSCImage*>(img);
			if (gscImg ){
				std::ofstream gscOutputFile(filePath);
				if(gscOutputFile.is_open()){
				//	if(std::ifstream(filePath)){
				//		std::cout << "[ERROR] File exists" << std::endl;
				//	}else {
					gscOutputFile << *gscImg;
					gscOutputFile.close();
					std::cout << "[OK] Export "<< tokenName << std::endl;
				//	}
					
				//	std::cout << "GSCIMAGE saved " << std::endl;
				}else {
					 std::cout << "[ERROR] Unable to create file" << std::endl;
						}
           			}
        		}
			}
		}
	
	} else {
    std::cout << "Invalid command\n";
		} 
    }else if (words[0] == "d") {
    if (words.size() == 2 && words[1][0] == '$') {
        std::string tokenName = words[1];
        int tokenPosition = db.getTokenPosition(tokenName);

       
          db.deleteImage(tokenName); // Call your deleteImage function
            std::cout << "[OK] Delete " << tokenName << std::endl;
    
  

   }else {
   	std::cout << "[ERROR] Unable to create file" << std::endl;
   }
    } 
	
	

	
	
	
	
	
	
	
	
	
	
	else if (words[0] == "n") {
    if (words.size() == 2 && words[1][0] == '$') {
        std::string tokenName = words[1];
        int tokenPosition = db.getTokenPosition(tokenName);

        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            
            if (img) {
                RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
                GSCImage* gscImg = dynamic_cast<GSCImage*>(img);
                
                if (rgbImage) {
                    // Apply color inversion using the operator and assignment
                    *img = !(*rgbImage);
                    std::cout << "[OK] Color Inversion " << tokenName << std::endl;
                } else if (gscImg) {
                    // Apply color inversion using the operator and assignment
                    *img = !(*gscImg);
                    std::cout << "[OK] Color Inversion " << tokenName << std::endl;
                } else {
                    std::cout << "[ERROR] Invalid image type for color inversion" << std::endl;
                }
            } else {
                std::cout << "[ERROR] Unable to apply color inversion" << std::endl;
            }
        }
    } else {
        std::cout << "Invalid command\n";
    }
	 
	 
	 
	 
	 
	 
	    // Implement your logic here
    } else if (words[0] == "z") {
    	if (words.size() == 2 && words[1][0] == '$'){
		 std::string tokenName = words[1];
        int tokenPosition = db.getTokenPosition(tokenName);

        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            
            if (img) {
                RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
                GSCImage* gscImg = dynamic_cast<GSCImage*>(img);
                
                if (rgbImage) {
                    // Apply color inversion using the operator and assignment
                    *img = ~(*rgbImage);
                    std::cout << "[OK] Equalize " << tokenName << std::endl;
                } else if (gscImg) {
                    // Apply color inversion using the operator and assignment
                    *img = ~(*gscImg);
                    std::cout << "[OK] Color Inversion " << tokenName << std::endl;
                } else {
                    std::cout << "[ERROR] Invalid image type for color inversion" << std::endl;
                }
            
        }else {
			std::cout << "Invalid command\n";
		}
	}
      }  
    } else if (words[0] == "m") {
    	if  (words.size() == 2 && words[1][0] == '$'){
		 std::string tokenName = words[1];
        int tokenPosition = db.getTokenPosition(tokenName);

        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            
            if (img) {
                RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
                GSCImage* gscImg = dynamic_cast<GSCImage*>(img);
                
                if (rgbImage) {
                    // Apply color inversion using the operator and assignment
                    *img = *(*rgbImage);
                    std::cout << "[OK] Mirror " << tokenName << std::endl;
                } else if (gscImg) {
                    // Apply color inversion using the operator and assignment
                    *img = *(*gscImg);
                    std::cout << "[OK] Mirror " << tokenName << std::endl;
                } 
            
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		}else {
				std::cout << "Invalid command\n";
		}
}
}
    } else if (words[0] == "g") {
    	if (words.size() == 2 && words[1][0] == '$'){
		std::string tokenName = words[1];
        int tokenPosition = db.getTokenPosition(tokenName);
        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
            if (rgbImage) {
                // Check if the image is already grayscale
                bool isGrayscale = true;
                for (int i = 0; i < rgbImage->getHeight(); i++) {
                    for (int j = 0; j < rgbImage->getWidth(); j++) {
                        if (rgbImage->getPixel(i, j).getRed() !=
                            rgbImage->getPixel(i, j).getGreen() ||
                            rgbImage->getPixel(i, j).getRed() !=
                            rgbImage->getPixel(i, j).getBlue()) {
                            isGrayscale = false;
                            break;
                        }
                    }
                    if (!isGrayscale) {
                        break;
                    }
                }

                if (isGrayscale) {
                    std::cout << "[NOP] Already grayscale " << tokenName << std::endl;
                } else {
                    GSCImage* gscImage = new GSCImage(*rgbImage);
                    db.deleteImage(tokenName); // Delete the previous RGB image
                    db.insertImage(gscImage, tokenName); // Insert the new grayscale image
                    std::cout << "[OK] Grayscale " << tokenName << std::endl;
                }
            } else {
                 std::cout << "[NOP] Already grayscale " << tokenName << std::endl;
            }
        }
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		}else {
			  std::cout << "Invalid command\n";
		}
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
        
    } else if (words[0] == "s") {
    if (words.size() == 4 && words[1][0] == '$' && words[2] == "by") {
        std::string tokenName = words[1];
        double factor = std::stod(words[3]);

        int tokenPosition = db.getTokenPosition(tokenName);
        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            if (img) {
                RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
                if (rgbImage) {
                    *rgbImage *= factor;
                    std::cout << "[OK] Scale " << tokenName << std::endl;
                } else {
                GSCImage* gscImage = dynamic_cast<GSCImage*>(img);	
                  if (gscImage) {
                    *gscImage *= factor;
                    std::cout << "[OK] Scale " << tokenName << std::endl;
                } 
                }
            } else {
                std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
            }
        }
    } else {
        std::cout << "Invalid command\n";
    }
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    	
    } else if (words[0] == "r") {
    if (words.size() == 5 && words[1][0] == '$' && words[2] == "clockwise") {
        std::string tokenName = words[1];
        int rotations = std::stoi(words[3]);

        int tokenPosition = db.getTokenPosition(tokenName);
        if (tokenPosition == -1) {
            std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
        } else {
            Image* img = db.getImage(tokenName);
            if (img) {
                if (rotations != 0) {
                    RGBImage* rgbImage = dynamic_cast<RGBImage*>(img);
                    if (rgbImage) {
                        *rgbImage += rotations;
                        std::cout << "[OK] Rotate " << tokenName << std::endl;
                    } else {
                        GSCImage* gscImage = dynamic_cast<GSCImage*>(img);
                        if (gscImage) {
                            *gscImage += rotations;
                            std::cout << "[OK] Rotate " << tokenName << std::endl;
                        } else {
                            std::cout << "[ERROR] Token " << tokenName << " is not a valid image\n";
                        }
                    }
                } else {
                    std::cout << "[OK] Rotate " << tokenName << " (No rotation needed)\n";
                }
            } else {
                std::cout << "[ERROR] Token " << tokenName << " does not exist\n";
            }
        }
    } else {
        std::cout << "Invalid command\n";
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    }else if (words[0]== "q"){
    	db.cleanup();
    	break;
	}


    

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//    // Define the stream with the provided content
//    std::istringstream stream("P2\n3 2 255\n0 255 128\n55 200 128\n");
//
//    // Create a GSCImage object from the stream
//    GSCImage gscImage(stream);
//
//    // Output GSCImage properties
//    std::cout << "GSCImage Width: " << gscImage.getWidth() << std::endl;
//    std::cout << "GSCImage Height: " << gscImage.getHeight() << std::endl;
//    std::cout << "Maximum Luminosity: " << gscImage.getMaxLuminocity() << std::endl;
//    std::cout << "\n";
//    
//    // Output pixel values from the GSCImage
//    for (int i = 0; i < gscImage.getHeight(); i++) {
//        for (int j = 0; j < gscImage.getWidth(); j++) {
//            std::cout << "GSCImage Pixel Value at (" << i << ", " << j << "): "
//                      << static_cast<int>(gscImage.getPixel(i, j).getValue()) << std::endl;
//        }
//    }
//    
//    // Test GSCImage operator+=
//    gscImage += 2;
//    
//    // Output modified pixel values from the GSCImage
//    std::cout << "\nModified GSCImage Pixel Values:\n";
//    for (int i = 0; i < gscImage.getHeight(); i++) {
//        for (int j = 0; j < gscImage.getWidth(); j++) {
//            std::cout << "Modified GSCImage Pixel Value at (" << i << ", " << j << "): "
//                      << static_cast<int>(gscImage.getPixel(i, j).getValue()) << std::endl;
//        }
//    }
//    
//    // Test GSCImage operator!
//    !gscImage;
//    
//    // Output modified pixel values from the GSCImage
//    std::cout << "\nModified GSCImage Pixel Values after ! operator:\n";
//    for (int i = 0; i < gscImage.getHeight(); i++) {
//        for (int j = 0; j < gscImage.getWidth(); j++) {
//            std::cout << "Modified GSCImage Pixel Value at (" << i << ", " << j << "): "
//                      << static_cast<int>(gscImage.getPixel(i, j).getValue()) << std::endl;
//        }
//    }
//    
//    // Create an RGBImage object from a separate provided stream
//   std::istringstream rgbStream("P3\n3 2 255\n255 0  0 255 255 0 0 255 255\n255 0 255 0 255 0 128 128 128\n");
//
//	
//    // Create an RGBImage object from the stream
//     RGBImage rgbImage(rgbStream);
//    
//    // Output RGBImage properties
//    std::cout << "\nRGBImage Width: " << rgbImage.getWidth() << std::endl;
//    std::cout << "RGBImage Height: " << rgbImage.getHeight() << std::endl;
//    std::cout << "Maximum Luminosity: " << rgbImage.getMaxLuminocity() << std::endl;
//    std::cout << "\n";
//    
//   //TEST########-OK
//    for (int i = 0; i < rgbImage.getHeight(); i++) {
//        for (int j = 0; j < rgbImage.getWidth(); j++) {
//            std::cout << "RGBImage Pixel Values at (" << i << ", " << j << "): "
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getRed()) << " "
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getGreen()) << " "
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getBlue()) << std::endl;
//        }
//    }
////    
//
////    // Test RGBImage operator*=
//   // rgbImage *= 0.5;
//  // !rgbImage; 
////    // Output modified pixel values from the RGBImage
////    std::cout << "\nModified RGBImage Pixel Values:\n";
////    for (int i = 0; i < rgbImage.getHeight(); i++) {
////        for (int j = 0; j < rgbImage.getWidth(); j++) {
////            std::cout << "Modified RGBImage Pixel Values at (" << i << ", " << j << "): "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getRed()) << " "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getGreen()) << " "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getBlue()) << std::endl;
////        }
////    }
////    
////    // Test RGBImage operator!
////    !rgbImage;
////    
////    // Output modified pixel values from the RGBImage
////    std::cout << "\nModified RGBImage Pixel Values after ! operator:\n";
////    for (int i = 0; i < rgbImage.getHeight(); i++) {
////        for (int j = 0; j < rgbImage.getWidth(); j++) {
////            std::cout << "Modified RGBImage Pixel Values at (" << i << ", " << j << "): "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getRed()) << " "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getGreen()) << " "
////                      << static_cast<int>(rgbImage.getPixel(i, j).getBlue()) << std::endl;
////        }
////    }
//    
////    // Create an output file for the modified GSCImage
////    std::ofstream gscOutputFile("output_gsc.pgm");
////    if (gscOutputFile.is_open()) {
////        gscOutputFile << gscImage;
////        gscOutputFile.close();
////        std::cout << "\nGSCImage saved to output_gsc.pgm" << std::endl;
////    } else {
////        std::cout << "\nUnable to open the GSCImage output file" << std::endl;
////    }
//    
//    // Create an output file for the modified RGBImage
//    std::ofstream rgbOutputFile("output_rgb.ppm");
//    if (rgbOutputFile.is_open()) {
//        rgbOutputFile << rgbImage;
//        rgbOutputFile.close();
//        std::cout << "RGBImage saved to output_rgb.ppm" << std::endl;
//    } else {
//        std::cout << "Unable to open the RGBImage output file" << std::endl;
//    }
//    
//
//std::istringstream rgbStream("P3\n3 2 255\n255 0 0 255 255 0 0 255 255\n255 0 255 0 255 0 128 128 128\n");
//    RGBImage rgbImage(rgbStream);
//
//    // Apply the ~ operator on the RGBImage
//    ~rgbImage;
//
//    // Print array values of RGBImage after applying ~ operator
//    std::cout << "RGBImage after ~ operator:\n";
//    for (int i = 0; i < rgbImage.getHeight(); i++) {
//        for (int j = 0; j < rgbImage.getWidth(); j++) {
//            std::cout << "("
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getRed()) << ","
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getGreen()) << ","
//                      << static_cast<int>(rgbImage.rgbpixel[i][j].getBlue()) << ") ";
//        }
//        std::cout << std::endl;
//    }
//
//    // Create a GSCImage from the RGBImage
//    GSCImage gscImage(rgbImage);
//
//    // Apply the ~ operator on the GSCImage
//    ~gscImage;
//
//    // Print array values of GSCImage after applying ~ operator
//    std::cout << "\nGSCImage after ~ operator:\n";
//    for (int i = 0; i < gscImage.getHeight(); i++) {
//        for (int j = 0; j < gscImage.getWidth(); j++) {
//            std::cout << static_cast<int>(gscImage.getPixel(i, j).getValue()) << " ";
//        }
//        std::cout << std::endl;
    }


    return 0;
}


