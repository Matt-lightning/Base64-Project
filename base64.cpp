#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "base64_class.h"


using namespace std;


int main(int argc, char* argv[]){
    try{    
    string encrypt_decrypt;

        cout << "_______________________________________" << endl;
        cout << "Hello please select what you want to do and make sure you have the correct file in the directory" << endl;
        cout << "If you want to exit enter stop or exit" << endl;
        cout << "Encrypt or Decrypt" << endl;
        cout << "_______________________________________" << endl;
        cin >>  encrypt_decrypt;

        if(encrypt_decrypt == "exit" || encrypt_decrypt == "Exit") return 0;
        if(encrypt_decrypt != "encrypt" && encrypt_decrypt != "Encrypt" && encrypt_decrypt != "decrypt" && encrypt_decrypt != "Decrypt"){
             throw std::runtime_error("Invalid input: expected 'encrypt' or 'decrypt'");
        }

            string filename;

            cout << "_______________________________________" << endl;
            cout << "Provide the name of the file with extension" << endl;
            cout << "_______________________________________" << endl;
            cin >> filename;

            string output_filename;
            cout << "_______________________________________" << endl;
            cout << "If you have a designated file for the output please provide now(With Exetension)" <<endl;
            cout << "If you do not enter (NO) for default file" << endl;
            cout << "_______________________________________" << endl;
            cin >> output_filename;

            ifstream unencrypted_file;
            unencrypted_file.open(filename);
            if(!unencrypted_file){
                throw std::runtime_error("Failed to open file: " + filename);
            }

            std::ostringstream oss;
            oss << unencrypted_file.rdbuf();
            std::string file_contents = oss.str();
            

            if(encrypt_decrypt == "encrypt" || encrypt_decrypt == "Encrypt"){
                Base64::encode(file_contents, output_filename);
            }
            else if(encrypt_decrypt == "decrypt" || encrypt_decrypt == "Decrypt"){
                Base64::decode(file_contents, output_filename);
            }
            else{
                cout << "Error: not a valid selection" << endl;
                return 1;
            }
            
            if(encrypt_decrypt == "encrypt" || encrypt_decrypt == "Encrypt"){
                cout << "Done with the encryption" << endl;
                cout << "Happy Privacy!!!" << endl;
            }
            if(encrypt_decrypt == "decrypt" || encrypt_decrypt == "Decrypt"){
                cout << "Done with the decryption" << endl;
                cout << "Happy Viewing!!!" << endl;
            }


            } catch (const std::ios_base::failure& e) {
                std::cerr << "File error: " << e.what() << std::endl;
                return 1;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid input: " << e.what() << std::endl;
                return 1;
            } catch (const std::exception& e) {
                std::cerr << "Standard exception: " << e.what() << std::endl;
                return 1;
            } catch (...) {
                std::cerr << "Unknown error has occurred (base64)" << std::endl;
                return 1;
            }
            return 0;
        }
    