64: wintroj.o
  x86_64-w64-mingw32-g++ -o trojan.exe wintroj.o -l ws2_32


32: wintroj.o
  1686-w64-mingw32-g++ -o trojan.exe wintroj.o -l ws2_32
  
  
wintroj.o: wintroj.cpp
  x86_64-w64-mingw32-g++ -c wintroj.cpp
 
clean:
  rm *.o *.c *.exe
