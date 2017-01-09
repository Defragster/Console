#ifndef _Console_
#define _Console_

#include <Arduino.h>
#include "Command.h"

class Console : public Stream {
  public:
    Console();
    virtual void begin();
    virtual void loop();

    void idle() { loop(); } // can't decide the name

	  void debugf(const char* format, ...);
	  void debugln(const char* s);
	  void debug(const char* s);
    void debugEnable(bool enable) { _debugEnabled = enable; };
    bool debugEnabled();

    void addCommand(Command* command) {  _commands->addCommand(command); };
    void removeCommand(Command* command) { command->removeCommand(); };

// low level virtual functions
	  int available();
	  int read();
    int peek();
    void flush();
    size_t write(uint8_t b);
    size_t write(const uint8_t *buf, size_t size);

  private:
    size_t debugPrefix(char* s);
    bool _debugEnabled = true;
    Command* _commands;
    void executeCommandLine();
    static const int _maxCommandLineLength = 100;
    char commandLine[_maxCommandLineLength];
    uint8_t _commandLineLength = 0;
};

#endif