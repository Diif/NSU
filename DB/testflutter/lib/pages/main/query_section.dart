import 'dart:ffi';

import 'package:duration/duration.dart';
import 'package:flutter/material.dart';
import 'package:testflutter/pages/main/model/changeable_substance.dart';
import 'package:testflutter/pages/main/model/changeable_supply_order.dart';
import 'package:testflutter/pages/main/model/changeable_tech.dart';
import 'package:testflutter/pages/main/model/substance.dart';
import 'package:testflutter/pages/main/model/supply_order.dart';
import 'package:testflutter/pages/main/model/tech_with_sub.dart';
import 'package:testflutter/pages/main/queries/p_query.dart';
import 'package:testflutter/pages/main/queries/ready_queries.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

import 'model/supply.dart';

Widget getQuerySection(
    void Function(void Function()) setState, BuildContext Function() context) {
  _setState = setState;
  _context = context;
  return Column(children: [
    Expanded(
        child: Row(
      children: [
        Expanded(child: _queriesListColumn()),
        Expanded(child: _selectedQueryColumn())
      ],
    ))
  ]);
}

late void Function(void Function()) _setState;
late BuildContext Function() _context;

PQuery _selectedQuery = queries[0];

Column _queriesListColumn() {
  return Column(
    children: [
      Expanded(
          child: ListView.builder(
              itemCount: queries.length,
              itemBuilder: (BuildContext b, int index) {
                return ListTile(
                    title: Text(queries[index].title),
                    onTap: () =>
                        _setState(() => _selectedQuery = queries[index]));
              })),
    ],
  );
}

Column _selectedQueryColumn() {
  Map<String, String> args = {};
  return Column(
    children: [
      Expanded(
          child: ListView.builder(
              itemCount: _selectedQuery.toSub.length,
              itemBuilder: (BuildContext b, int index) {
                return ListTile(
                    title: TextField(
                  onChanged: (str) => args[_selectedQuery.toSub[index]] = str,
                  decoration:
                      InputDecoration(hintText: _selectedQuery.hints[index]),
                ));
              })),
      Container(
          color: Colors.amber,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              IconButton(onPressed: () async{
                List<TableRow> rows = [_createHeaderRow(_selectedQuery)];
                rows.addAll(await executeQuery(_selectedQuery, args));
                _createResultDialog(_context(), rows);
              }, icon: const Icon(Icons.play_arrow))
            ],
          ))
    ],
  );
}

TableRow _createHeaderRow(PQuery query){
  List<Text> res = [];
  for (final el in query.labels){
    res.add(Text(el));
  }
  return TableRow(children: res);
}

void _createResultDialog(BuildContext context, List<TableRow> rows) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        return AlertDialog(
          title: const Text("Результат запроса"),
          content: SizedBox(width: 750,child: Table(children: rows),),
          actions: [
            TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text("Ок")),
          ],
          actionsAlignment: MainAxisAlignment.spaceAround,
        );
      });
}
