#ifndef GITBranches_H
#define GITBranches_H
#include <ArduinoSTL.h>

enum class DataState {
  STARTED = 0,
  COMPLETE = 1
};


class GitBranches {
  public:
    GitBranches(String branchName): _branchName(branchName), _state(DataState){
      
    }

    void update(){
      // check to see if theres new serial data for branches
      // ref: http://forum.arduino.cc/index.php?topic=39922.0
      while(Serial.available() > 0){
        _incomingData = Serial.read();
        if(_incomingData == 'branches: <') {
          _state = DataState::STARTED;
          started = true;
          ended = false;
        } else if(_incomingData == '>') {
          _state = DataState::COMPLETE;
          ended = true;
          break; // Break out of the while loop
        } else {
          rohre[serialIn] = _incomingData;
          serialIn++;
          rohre[serialIn] = '\0';
        }
      }
    }

  private:
    String _branchName;
    String _incomingData;
    DataState _state;
}

#endif
