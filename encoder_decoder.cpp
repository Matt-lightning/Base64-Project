#include "base64_class.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <bitset>

using namespace std;

int Base64::padding(string text){
    int len = text.length();
    int remainder = len % 3;
    return remainder;
    
}

bool Base64::isvalidinput(const string& filename){
    if(!filename.length() % 4 != 0){
        return false;
    }

    for(size_t i; i < filename.length(); i++){
        char check = filename[i];
            
        if(isalnum(check) || check == '+' || check == '/'){
            continue;
        }

        if(check == '=' && (i >= filename.length() - 2)){
            continue;
        }

        return false;
    }
        
    return true;
}

bool Base64::isvalidcharacter(const bitset<8>& byte){
    unsigned long value = byte.to_ulong();
        return (value >= 65 && value <= 90)  ||  // A-Z
            (value >= 97 && value <= 122) ||  // a-z
            (value >= 48 && value <= 57)  ||  // 0-9
            (value == 43) || (value == 47) || 
            (value == 9) || (value == 10) || 
            (value == 11) || (value == 12) ||
           (value == 13) || (value == 32)|| // + /
            (value == 61);                     // =

}

const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

void Base64::encode(const std::string& unencrypted_text, const std::string& filename){
    try{
        int padding_needed = padding(unencrypted_text);
        ofstream output_file;
        if(filename != "no" && filename != "No" && filename != "NO"){
            output_file.open(filename);
            if(!output_file){
                throw runtime_error("Error could not open file");
            }
         }else{
            output_file.open("encrypted_file.txt");
            if(!output_file){
                throw runtime_error("Error: Could not open default file encrypted_file.txt");
            }
        }

            vector<string> group;
            // cout << unencrypted_text << endl;
            for(size_t i = 0; i < unencrypted_text.size(); i +=3){
                group.push_back(unencrypted_text.substr(i,3));
            }

            vector<bitset<6>> six_bit_group;
            string eight_bit_group;

            for(const auto& str : group){
                // vector<bitset<8>> eight_bit_group;
                bitset<8> buffer;
                for(size_t i = 0; i < str.size(); i++){
                    int ascii_value = static_cast<int>(str[i]);
                    buffer = ascii_value;
                    eight_bit_group += buffer.to_string();
                }
            }

            for(size_t i = 0; i < eight_bit_group.size(); i+= 6){
                string conv_group =eight_bit_group.substr(i,6);
                bitset<6> buffer(conv_group);
                six_bit_group.push_back(buffer);
            }

            string encoded;
            string map;
            for(auto& bit : six_bit_group){
                int decimal = bit.to_ulong();
                map += base64_chars[decimal];
            }
 
            switch(padding_needed){
                case 0: 
                    encoded = map;
                    break;
                case 1:
                    encoded = map + "=";
                    break;
                case 2:
                    encoded = map + "==";
                    break;
                default:
                    throw runtime_error("Error: Invalid padding needed");
            }

            output_file << encoded;
         }
         catch(const runtime_error& e){
            cerr << e.what() << endl;
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Out of range error: " << e.what() << endl;
        } catch (...) {
            cerr << "An unknown error occurred(encdoer_decoder)" << endl;
        }
    }

void Base64::decode(const string& encrypted_text, const std::string& filename){

    try{
        ofstream output_file;
        if(filename != "no" && filename != "No" && filename != "NO"){
            output_file.open(filename);
            if(!output_file){
                throw runtime_error("Error could not open file");
            }
         }else{
            output_file.open("unencrypted_text.txt");
            if(!output_file){
                throw runtime_error("Error: Could not open default file unencrypted_text.txt");
            }
        }

        if(!isvalidinput(encrypted_text)){
            throw invalid_argument("Invalid Base64 input");
        }

        size_t padding_count = 0;
        for (int i = encrypted_text.length() - 1; i >= 0 && encrypted_text[i] == '='; --i) {
            padding_count++;
        }

        vector<bitset<6>> reverse_six_bit;
        for (char c : encrypted_text) {
            if(c == '='){
                break;
            }
            if(c == '\n'){
                continue;
            }

            string::size_type found = base64_chars.find(c);
            if (found == string::npos) throw invalid_argument("Invalid Base64 character");
            bitset<6> buffer(found);
            reverse_six_bit.push_back(buffer);
            
        }

        vector<string> reverse_eight_bit;
        string buffer_string;
        for(auto& bit: reverse_six_bit){    
            buffer_string += bit.to_string();
        }

        if (padding_count == 1) {
        buffer_string.erase(buffer_string.end() - 2, buffer_string.end()); // Remove 2 bits
        } else if (padding_count == 2) {
        buffer_string.erase(buffer_string.end() - 4, buffer_string.end()); // Remove 4 bits
        }

        string final_string;
        cout << "Byte: " << endl;
        for(size_t i = 0; i+8 < buffer_string.size(); i += 8){
            bitset<8> byte(buffer_string.substr(i,8));
            if(isvalidcharacter(byte)){ 
                final_string += static_cast<char>(byte.to_ulong());
            }
        }

        cout << "test" << endl;
        output_file << final_string;

    }catch(const runtime_error& e){
        cerr << e.what() << endl;
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
    } catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
    } catch (...) {
        cerr << "An unknown error occurred(encdoer_decoder)" << endl;
    }
    

}