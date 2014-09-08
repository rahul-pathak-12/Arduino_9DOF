% A Matlab Function that closes the serial connection

clc
clear all

if ~isempty(instrfind)
	fclose(instrfind)
	delete(instrfind)
end

close all
clc
disp('[SERIAL PORT CLOSED]')