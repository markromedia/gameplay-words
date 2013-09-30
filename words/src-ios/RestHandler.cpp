//
//  RestHandler.cpp
//  words
//
//  Created by Mark Udit on 9/29/13.
//
//
#ifdef __APPLE__
#include "../src/rest_handler.hpp"

RestHandler* RestHandler::instance = NULL;

/// Initialises this object.
void RestHandler::Init(){
    
}

/// Returns singleton
/// @return	null if it fails, else.
RestHandler* RestHandler::get(){
    return NULL;
}

/// Query if this object has internet connection.
/// @return	true if internet connection, false if not.
bool RestHandler::HasInternetConnection(){
    return false;
}

/// Submit round log to the server
/// @param [in,out]	round_log	If non-null, the round log.
void RestHandler::SubmitRoundLog(RoundLog* round_log){
    
}

#endif


