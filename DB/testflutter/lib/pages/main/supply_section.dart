import 'dart:ffi';

import 'package:duration/duration.dart';
import 'package:flutter/material.dart';
import 'package:testflutter/pages/main/model/changeable_substance.dart';
import 'package:testflutter/pages/main/model/changeable_supply_order.dart';
import 'package:testflutter/pages/main/model/changeable_tech.dart';
import 'package:testflutter/pages/main/model/substance.dart';
import 'package:testflutter/pages/main/model/supply_order.dart';
import 'package:testflutter/pages/main/model/tech_with_sub.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

import 'model/supply.dart';

Widget getSupplySection(
    void Function(void Function()) setState, BuildContext Function() context) {
  _setState = setState;
  _context = context;
  return Column(children: [
    Expanded(
        child: Row(
      children: [
        Expanded(child: _searchSupplyOrderColumn(_orders)),
        Expanded(child: _orderInfoColumn())
      ],
    ))
  ]);
}

late void Function(void Function()) _setState;
late BuildContext Function() _context;
final List<SupplyOrder> _orders = [];
final List<Supply> _supplies = [];
SupplyOrder _selectedOrder =
    SupplyOrder(-1, DateTime.now(), -1, -1, -1, "");
late ChangeableTech _editableTech;

Column _searchSupplyOrderColumn(List<SupplyOrder> orders) {
  return Column(children: [
    Expanded(
        child: ListView.builder(
            itemCount: orders.length,
            itemBuilder: (BuildContext b, int index) {
              return ListTile(
                  title: Text(orders[index].time.toLocal().toString()),
                  onTap: () => _setState(() => _selectedOrder = orders[index]) );
            })),
    Container(
      color: Colors.amber,
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          IconButton(
              onPressed: () => _createAddOrderDialog(_context()),
              icon: const Icon(
                Icons.add,
                color: Colors.black,
              )),
          IconButton(
            // onPressed: () => _createAddTechDialog(_context()),
              onPressed: () async {
                orders.clear();
                await searchSupplyOrders(orders);
                _setState(() {});
              },
              icon: const Icon(
                Icons.refresh,
                color: Colors.black,
              ))
        ],
      ),
    )
  ]);
}

late ChangeableSupplyOrder _orderToAdd;

void _createAddOrderDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        _orderToAdd = ChangeableSupplyOrder();
        return AlertDialog(
          title: const Text("Запросить поставку"),
          content: Column(children: [
            Expanded(
                child: TextField(
              decoration:
                  const InputDecoration(hintText: "Введите название лекарства"),
              onChanged: (str) => _orderToAdd.subName = str,
            )),
            Expanded(
                child: TextField(
              decoration: const InputDecoration(
                  hintText:
                      "Введите количество"),
                  onChanged: (str) => _orderToAdd.countToReceive = int.parse(str),
            )),
          ]),
          actions: [
            TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text("Отмена")),
            TextButton(
                onPressed: () {
                  addSupplyOrder(_orderToAdd);
                  Navigator.of(context).pop();
                },
                child: const Text("Создать"))
          ],
          actionsAlignment: MainAxisAlignment.spaceAround,
        );
      });
}

Column _orderInfoColumn() {
  var tc = TextEditingController(text: _selectedOrder.subName);
  return Column(
    children: [
      Expanded(
          child: Container(
              color: Colors.amberAccent,
              child: ListView(
                children: [
                  ListTile(
                      title: TextField(
                          enabled: false,
                          decoration: InputDecoration(
                              hintText: _selectedOrder.id.toString())),
                      subtitle: const Text("ID заказа")),
                  ListTile(
                      title: TextField(
                          controller: tc,
                          enabled: true,
                          decoration: InputDecoration(
                              hintText: _selectedOrder.subName)),
                      subtitle: const Text("Название лекарства")),
                  ListTile(
                      title: TextField(
                        enabled: false,
                        decoration: InputDecoration(
                          hintText: _selectedOrder.time.toLocal().toString()
                        ),
                      ),
                      subtitle: const Text("Время создания заказа")),
                  ListTile(
                      title: TextField(
                        enabled: false,
                        keyboardType: TextInputType.text,
                        maxLines: 1,
                        decoration: InputDecoration(
                            hintText:
                                _selectedOrder.receivedCount.toString(),
                            border: InputBorder.none),
                      ),
                      subtitle: const Text("Полученное количество")),
                  ListTile(
                      title: TextField(
                          enabled: true,
                          decoration: InputDecoration(
                              hintText:
                                  _selectedOrder.countToReceive.toString()),
                          onChanged: (val) =>
                              _editableTech.medCount = int.parse(val)),
                      subtitle: const Text("Запрашиваемое количество")),
                ],
              ))),
      Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            IconButton(
                onPressed: () => _createAddSupplyDialog(_context()),
                icon: const Icon(Icons.add_business))
          ],
        ),
      )
    ],
  );
}

int _supplyCountToSave = 0;

void _createAddSupplyDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        _orderToAdd = ChangeableSupplyOrder();
        return AlertDialog(
          title: const Text("Зарегистрировать поставку"),
          content: Column(children: [
            Expanded(
                child: ListTile(
                  title: TextField(
                    enabled: false,
                    decoration: InputDecoration(hintText: _selectedOrder.subName),
                  ),
                  subtitle: const Text("Наименование лекарства"),
                )),
            Expanded(
                child: TextField(
                  decoration: const InputDecoration(
                      hintText:
                      "Введите количество"),
                  onChanged: (str) => _supplyCountToSave = int.parse(str),
                )),
          ]),
          actions: [
            TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text("Отмена")),
            TextButton(
                onPressed: () {
                  addSupply(_selectedOrder.id, _supplyCountToSave);
                  Navigator.of(context).pop();
                },
                child: const Text("Создать"))
          ],
          actionsAlignment: MainAxisAlignment.spaceAround,
        );
      });
}
