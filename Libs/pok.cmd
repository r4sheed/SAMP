@ECHO ON

FOR /F "tokens=*" %%s IN ('DIR /S /B /A:-D "%CD%\EN_*.txt"') DO CALL :CP "%%s"

pause
GOTO :eof

:CP
SET _RU_NAME=%~nx1
SET _RU_NAME=RU_%_RU_NAME:~3%
SET _RU_NAME=%~dp1%_RU_NAME%
IF NOT EXIST "%_RU_NAME%" COPY "%~1" "%_RU_NAME%"
GOTO :eof