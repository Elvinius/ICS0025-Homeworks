#pragma once
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "Data.h"
#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

#define BUFSIZE 512
Data datas;
atomic_bool stop_server = false;

int serverConnect() {

    HANDLE hPipe;
    char  chBuf[BUFSIZE];
    BOOL   fSuccess = FALSE;
    DWORD  cbRead, cbToWrite, cbWritten, dwMode;
    const char* pReady = "ready";
    const char* pStop = "stop";
    list<string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    while (1)
    {
        hPipe = CreateFile(
            TEXT("\\\\.\\pipe\\ICS0025"),  
            GENERIC_READ |  
            GENERIC_WRITE,
            0,              
            NULL, 
            OPEN_EXISTING, 
            0,
            NULL);     

        if (hPipe != INVALID_HANDLE_VALUE)
            break;

        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            printf("Can't open the pipe");
            return -1;
        }

        if (!WaitNamedPipe(TEXT("\\\\.\\pipe\\ICS0025"), 15000))
        {
            printf("Timed out after 15 seconds.");
            return -1;
        }
    }

    dwMode = PIPE_READMODE_MESSAGE;
    fSuccess = SetNamedPipeHandleState(
        hPipe,     
        &dwMode,  
        NULL,     
        NULL);    
    if (!fSuccess)
    {
        printf("SetNamedPipeHandleState failed.\n");
        return -1;
    }
    do
    {
        if (stop_server) {
            fSuccess = WriteFile(
                hPipe,               
                pStop,             
                5,             
                &cbWritten,            
                NULL);                 
        }

        fSuccess = WriteFile(
            hPipe,                  
            pReady,            
            6,             
            &cbWritten,  
            NULL);                 

        if (!fSuccess)
        {
            printf("WriteFile to pipe failed.\n");
            return -1;
        }

        printf("\nMessage successfully sent\n");

        fSuccess = ReadFile(
            hPipe,   
            chBuf, 
            BUFSIZE * sizeof(char), 
            &cbRead, 
            NULL);  

        if (!fSuccess && GetLastError() != ERROR_MORE_DATA) {
            printf("Lost connection to the pipe");
            break;
        }

        char  group = chBuf[0];
        int subgroup = atoi(&chBuf[2]);
        char* delimiter = &(chBuf[5]);
        string* itemstring = new string;
        while (*delimiter != '>') {
            if (*delimiter != '<')
                itemstring->push_back(*delimiter);
            delimiter++;
        }
        delimiter += 2;
        int day = atoi(delimiter);
        delimiter += 3;
        string sMonth = string();
        for (int cMonth = 0; cMonth < 3; cMonth++) {
            sMonth.push_back(*delimiter);
            delimiter++;
        }
        int nMonth = distance(months.begin(), find(months.begin(), months.end(), sMonth)) + 1;
        delimiter++;
        int year = atoi(delimiter);
        std::chrono::milliseconds waitingTime(500);
        Date itemDate(day, nMonth, year);
        datas.InsertItem(group, subgroup, *itemstring, itemDate);
    } while (fSuccess);  
    return 1;
}

int main() {

    bool check = true;
    printf("Choose one of the commands:\n1)connect\n2)stop\n3)exit\n");
    string user_input;
    int userChoice;
    while (check) {
        cin >> user_input;
        if (user_input == "connect") {
            userChoice = 0;
        }
        else if (user_input == "stop") {
            userChoice = 1;
        }
        else if (user_input == "exit") {
            userChoice = 2;
        }
        else {
            userChoice = 3;
        }

        switch (userChoice) {
        case 0: {
            if (stop_server) {
                stop_server = false;
            }
            thread connectThread(serverConnect);
            connectThread.detach();
            break;
        }

        case 1: {
            if (stop_server) {
                printf("Connection closed");
                break;
            }
            stop_server = true;
            break;
        }
        case 2: {
            check = false;
            printf("Item list:");            
            datas.PrintAll();
            break;
        }
        default: {
            printf("Command is not available");
            break;
        }
        }
    }
	return 0;
}