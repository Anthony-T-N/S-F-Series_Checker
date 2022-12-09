// [S]-[F]-Series_Checker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <map>
#include <chrono>

std::vector<std::string> line_checker(std::map<int, std::string> path_list_map, std::string user_input)
{
    std::ifstream input_file;
    input_file.open(path_list_map[std::stoi(user_input)]);
    std::cout << "\n" << "[!] Selection: " << path_list_map[std::stoi(user_input)] << "\n\n";

    std::vector<std::string> input_file_line_vec;
    std::string input_file_line;

    std::vector<std::string> started_vector;
    std::vector<std::string> finished_vector;
    std::vector<std::string> final_vector;

    int i = 1;
    while (std::getline(input_file, input_file_line))
    {
        // Line must either have "Started" or "Finished".
        // Based on "Started" or "Finished" text, place sub-text into correct vector.
        // Compare vectors for unique items.

        if (input_file_line.find("Started") != std::string::npos || input_file_line.find("<S>") != std::string::npos)
        {
            started_vector.push_back(input_file_line.substr(input_file_line.find("Started") + 7, input_file_line.find("\"")));
            input_file_line = input_file_line.substr(input_file_line.find("Started") + 7, input_file_line.find("\""));
            //std::cout << i << ")" << input_file_line << "\n";
            final_vector.push_back(input_file_line);
            i++;
        }
        else if (input_file_line.find("Finished") != std::string::npos || input_file_line.find("<F>") != std::string::npos)
        {
            finished_vector.push_back(input_file_line.substr(input_file_line.find("Finished") + 8, input_file_line.find("\"")));
            input_file_line = input_file_line.substr(input_file_line.find("Finished") + 8, input_file_line.find("\""));
            //std::cout << i << ")" << input_file_line << "\n";
            final_vector.push_back(input_file_line);
            i++;
        }
        else
        {
            std::cout << "\033[31m" << "[!] Missing Start/Finish Key" << "\033[0m" << "\n";
            std::cout << i << ")" << input_file_line << "\n";
            i++;
        }
    }

    sort(started_vector.begin(), started_vector.end());
    sort(finished_vector.begin(), finished_vector.end());

    for (int i = 0; i <= started_vector.size() - 1; i++)
    {
        //std::cout << "i: " << i << "\n";
        for (int j = 0; j <= finished_vector.size() - 1; j++)
        {
            //std::cout << started_vector[i] << " " << finished_vector[j] << "\n";
            if (started_vector[i] == finished_vector[j])
            {
                started_vector.erase(started_vector.begin() + i);
                finished_vector.erase(finished_vector.begin() + j);
                i--;
                break;
            }
        }
    }
    /*
    std::cout << "\nstarted_vector_Print:\n";
    for (int i = 0; i <= started_vector.size() - 1; i++)
    {
        std::cout << started_vector[i] << "\n";
    }
    std::cout << "\nfinished_vector_Print:\n";
    for (int i = 0; i <= finished_vector.size() - 1; i++)
    {
        std::cout << finished_vector[i] << "\n";
    }
    */

    int j = 1;
    std::ifstream input_filet;
    input_filet.open(path_list_map[std::stoi(user_input)]);
    std::cout << "\n" << "[!] Start/Finish Vector" << "\n";
    while (std::getline(input_filet, input_file_line))
    {
        if (input_file_line.find("Started") != std::string::npos || input_file_line.find("<S>") != std::string::npos)
        {
            for (int i = 0; i <= started_vector.size() - 1; i++)
            {
                if (input_file_line.find(started_vector[i]) != std::string::npos)
                {
                    std::cout << j << ") " << input_file_line << "\n";
                    break;
                }
            }
        }
        else if (input_file_line.find("Finished") != std::string::npos || input_file_line.find("<F>") != std::string::npos)
        {
            for (int i = 0; i <= finished_vector.size() - 1; i++)
            {
                if (input_file_line.find(finished_vector[i]) != std::string::npos)
                {
                    std::cout << j << ") " << "\033[31m" << input_file_line << "\033[0m" << "\n";
                    break;
                }
            }
        }
        j++;
    }
    input_file.close();

    /*
    sort(final_vector.begin(), final_vector.end());
    final_vector.erase(unique(final_vector.begin(), final_vector.end()), final_vector.end());
    std::cout << "\nFinal_Vector_Print:\n";
    for (int i = 0; i <= final_vector.size() - 1; i++)
    {
        std::cout << final_vector[i] << "\n";
    }
    */

    return input_file_line_vec;
}

int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- [S]-[F]-Series_Checker console application" << "\n";
    std::cout << "- Console Application Version: 1.0" << "\n";
    std::cout << "- Created By: Anthony-T-N." << "\n";
    std::cout << "- Executable Location: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";

    std::map<int, std::string> path_list_map;
    std::vector<std::string> url_list;
    std::string path = std::filesystem::current_path().generic_string();
    int iteration = 0;
    std::cout << "[!] Current text files:" << "\n";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if ((entry.path().generic_string().substr(entry.path().generic_string().find_last_of("//") + 1)).find(".txt") != std::string::npos ||
            (entry.path().generic_string().substr(entry.path().generic_string().find_last_of("//") + 1)).find(".csv") != std::string::npos)
        {
            std::cout << "[" << iteration << "] " << entry.path().generic_string().substr(entry.path().generic_string().find_last_of("//") + 1) << "\n";
            path_list_map.insert(std::make_pair(iteration, entry.path().generic_string().substr(entry.path().generic_string().find_last_of("//") + 1)));
            iteration++;
        }
    }
    std::string user_input;
    while (true)
    {
        std::cout << "\n" << "[=] Make Selection: " << "[0-" << iteration - 1 << "]" << "\n";
        std::cout << "> ";
        std::getline(std::cin, user_input);

        if (user_input.find_first_not_of("0123456789") != std::string::npos || user_input.empty())
        {
            std::cout << "[-] Invalid input - Please try again" << "\n";
        }
        else if (std::stoi(user_input) > iteration - 1)
        {
            std::cout << "[-] Invalid input - Please try again" << "\n";
        }
        else
        {
            break;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    line_checker(path_list_map, user_input);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\n" << duration.count() << " microseconds" << "\n";

    std::cout << "\n" << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n";
    std::cin.get();
    return 0;
}

/*
* 
Project Planand Design

Brief : Console application reads text file and flags unique lines.

[Version 1]
=== Minimum Functions ===
[-] 

=== Flow map ===
1) Reads file -> 2) Flag unique lines -> 3) Print out lines.

*/
