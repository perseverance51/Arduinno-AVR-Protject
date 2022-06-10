#include <AT25F512.h>
#include <SoftwareSerial.h>
#include <hex.h>

AT25F512 mem(10,9);//cs,wp引脚
String command;

void setup(){
  Serial.begin(9600);
  Serial.println("Device ID is |\t"+hex(mem.info()));
  Serial.print(">");
}

void loop() {
  if(Serial.available()){
    byte ch =(byte) Serial.read();
    if(ch==32){command.remove(command.length()-1);//32--对应的按键码是空格键
    Serial.println("clear data...");}
    else{ command+=char(ch);
    Serial.println(String(ch));
    }
  }
  if(command.indexOf(char(13))>-1){
    Serial.println("Command string | "+command);
    command.toLowerCase();
    if(command.indexOf("write")>-1){
      int addr = command.substring(command.indexOf("(")+1,command.indexOf(",")).toInt();
      byte val[256];
      byte i=0;
      command = command.substring(command.indexOf(",")+1);
      while(command.indexOf(",")>-1){
        val[i++] = command.substring(0,command.indexOf(",")).toInt();
        command = command.substring(command.indexOf(",")+1);
      }
      val[i++] = command.substring(0,command.indexOf(")")).toInt();
      Serial.print("Got byte array [");
      for(int j=0;j<i;++j)
        if(j)
          Serial.print(","+hex(val[j]));
        else
          Serial.print(hex(val[j]));
      Serial.println("]");
      Serial.print("Programming...\t");
      mem.program(addr,val,i);
      Serial.println("Done.");
    }else if(command.indexOf("read")>-1){
      int addr = command.substring(command.indexOf("(")+1,command.indexOf(")")).toInt();
      Serial.println("Byte form address 0x"+hex(addr)+" |\t"+hex(mem.read(addr)));
    }else if(command.indexOf("info")>-1)
      Serial.println("Device ID is |\t"+hex(mem.info()));
    else if(command.indexOf("statusset")>-1){
      byte st = command.substring(command.indexOf('(')+1,command.indexOf(')')).toInt();
      Serial.println("Writing register state |\t"+bin(st));
      mem.statusSet(st);
    }else if(command.indexOf("status")>-1)
      Serial.println("Status register |\t"+bin(mem.status()));
    else if(command.indexOf("clearsector")>-1){
      int addr = command.substring(command.indexOf("(")+1,command.indexOf(")")).toInt();
      Serial.print("Clearing sector 0x"+hex(addr)+"...\t");
      mem.clearSector(addr);
      Serial.println("Clear.");
    }else if(command.indexOf("clear")>-1){
      Serial.print("Clearing chip...\t");
      mem.clearChip();
      Serial.println("Clear.");
    }else if(command.indexOf("printstr")>-1){
      Serial.println("Printing chip memory...\t");
      Serial.println("Press any key to stop...\t");
      Serial.println();
      Serial.print("         | ");
      for(byte i=0;i<32;++i)
        Serial.print(hex(i)+" ");
      Serial.println();
      Serial.print("---------+");
      for(byte i=0;i<32;++i)
        Serial.print("---");
      for(unsigned long i=0;i<0xFFFF;++i){
        if(i%32==0){
          Serial.println();
          Serial.print(hex(i)+" | ");
        }
        Serial.print(" "+String((char)mem.read(i))+" ");
        if(Serial.available())break;
      }
      Serial.println();
      if(Serial.available())
        Serial.println("Print process was terminated.");
      else
        Serial.println("That's all.");
      Serial.println();
    }else if(command.indexOf("print")>-1){
      Serial.println("Printing chip memory...\t");
      Serial.println("Press any key to stop...\t");
      Serial.println();
      Serial.print("         | ");
      for(byte i=0;i<32;++i)
        Serial.print(hex(i)+" ");
      Serial.println();
      Serial.print("---------+");
      for(byte i=0;i<32;++i)
        Serial.print("---");
      for(unsigned long i=0;i<0xFFFF;++i){
        if(i%32==0){
          Serial.println();
          Serial.print(hex(i)+" | ");
        }
        Serial.print(hex(mem.read(i))+" ");
        if(Serial.available())break;
      }
      Serial.println();
      if(Serial.available())
        Serial.println("Print process was terminated.");
      else
        Serial.println("That's all.");
      Serial.println();
    }
    command = "";
    Serial.print(">");
  }  
}
