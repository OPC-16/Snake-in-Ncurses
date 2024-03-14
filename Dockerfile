FROM gcc:latest

WORKDIR /snake

COPY . /snake

RUN g++ -o output -lncurses main.cpp

CMD [ "./output" ]
