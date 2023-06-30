FROM ubuntu:18.04

# Автор: Межитов Исмаил Равильевич 221-352

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install qt5-default -y
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake
RUN apt-get install build-essential -y

WORKDIR /352_Mezhitov_Ismail

COPY . .

RUN qmake echoServer1.pro && make

CMD ["./echoServer1", "Server started"]