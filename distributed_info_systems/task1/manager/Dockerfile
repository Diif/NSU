FROM alpine:3.19.1

WORKDIR /manager

RUN apk update
RUN apk add openjdk21-jre

COPY . .

EXPOSE 8080

RUN sh ./gradlew build -x test

CMD ./gradlew build && java -jar ./build/libs/manager-0.0.1-SNAPSHOT.jar
