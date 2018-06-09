make > input.txt
pro < input.txt > 1.txt
bf < input.txt > 2.txt
fc 1.txt 2.txt
if errorlevel 1 pause
%0