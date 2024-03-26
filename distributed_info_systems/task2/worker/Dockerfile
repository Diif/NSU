FROM alpine:3.19.1

WORKDIR /worker

RUN apk update
RUN apk add openjdk21-jre

COPY . .

EXPOSE 8080

RUN sh ./gradlew build -x test

CMD sh ./gradlew build -x test && java -jar ./build/libs/worker-0.0.1-SNAPSHOT.jar
