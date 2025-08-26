//see Making Embedded Systems, https://g.co/kgs/kzuSy8
#include <stdio.h>
#include <string.h>

typedef void(*functionPointerType)(void);

typedef struct {
    char const *name;
    functionPointerType execute;
    char const *help;
} commandStruct;

void CmdVersion(void){printf("Version\n");}
void CmdFlashTest(void){printf("Flash test\n");}
void CmdBlinkLed(void){printf("Blink blink\n");}
void CmdTmpl(void){printf("...template\n");}
void CmdHelp(void);

const commandStruct commands[] = {
    {"ver", &CmdVersion, "Display firmware version"},
    {"flashTest", &CmdFlashTest, "Runs the flash unit test, printis number of errors upon completion"},
    {"blinkLed", &CmdBlinkLed, "Sets the LED to blink at a desired rate (parameter: frequency (Hz))"},
    {"template", &CmdTmpl, "Template for new cmds."}, 
    {"help", &CmdHelp, "Help menu."},
    {"", 0, ""}  //End of table indicator. MUST BE LAST!!!
};

void CmdHandler(char* cmd)
{
    int i = 0;
    while(commands[i].execute > 0)
    {
        if(!strcmp(commands[i].name, cmd))
        {
            printf("cmd: %s. %s() => ", cmd, commands[i].name);
            (*commands[i].execute)();
            return;
        }
        i++;
    }
    printf("WARNING: No matching cmd for %s.\n", cmd);
}

void TestCommandsArr()
{
    int i = 0;
    while(commands[i].execute > 0)
    {
        printf("%s : ", commands[i].name);
        (*commands[i].execute)();
        i++;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        CmdHandler(argv[1]);
    } else {
        // TestCommandsArr();
        CmdHandler("help");
    }

    return 0;
}

void CmdHelp(void){
    printf("The commands are:\n");
    int i = 0;
    while(commands[i].execute > 0){
        if (strcmp(commands[i].name, "help")) {
          printf("cmd: %s\n%s\n\n", commands[i].name, commands[i].help);
        }
        i++;
    }
}

