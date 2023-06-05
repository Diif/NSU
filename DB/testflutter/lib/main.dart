import 'package:flutter/material.dart';
import 'package:postgres/postgres.dart';
import 'package:testflutter/pages/main/page_dispatcher.dart';
import 'package:testflutter/pages/main/queries/ready_queries.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

void main() async {
  PostgreSQLConnection connection = PostgreSQLConnection(
      "localhost", 5432, "postgres",
      username: "prozella", password: "6215");
  connection.open();
  init(connection);
  fillQueries();
  runApp(MaterialApp(home: PageDispatcher()));
}
