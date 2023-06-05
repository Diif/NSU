import 'package:flutter/material.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

import 'model/changeagble_client.dart';
import 'model/client.dart';
import 'model/order.dart';
import 'model/order_sub.dart';
import 'model/substance.dart';

late void Function(void Function()) _setState;
late BuildContext Function() _context;

final List<Client> _clients = [];
Client _selectedClient = const Client(-1, "", "", "", "");
late ChangeableClient _clientToEdit;

final List<Order> _orders = [];
Order _selectedOrder = Order(-1, -1, -1, null, null, DateTime.now());
final Map<int, String> _stages = {};

final List<OrderSub> _subsInOrder = [];
ChangeableClient _clientToAdd =
    ChangeableClient.fromClient(const Client(-1, "", "", "", ""));

Widget getMainSection(
    void Function(void Function()) setState, BuildContext Function() context) {
  _setState = setState;
  _context = context;
  return Row(children: [
    Expanded(child: _fstColumn()),
    Expanded(child: _scdColumn()),
    Expanded(child: _trdColumn())
  ]);
}

Column _fstColumn() {
  return Column(children: [
    Row(
      children: [
        Expanded(
            child: TextField(
          decoration: const InputDecoration(hintText: "Введите номер..."),
          onChanged: (phone) async {
            await searchClients(phone, _clients);
            _setState(() {});
          },
          onSubmitted: (phone) async {
            await searchClients(phone, _clients);
            _setState(() {});
          },
        )),
        const Icon(Icons.search)
      ],
    ),
    Expanded(
        child: ListView.builder(
            itemCount: _clients.length,
            itemBuilder: (BuildContext context, int index) {
              return ListTile(
                title: Text(_clients[index].phone),
                enabled: true,
                onTap: () async {
                  _selectedClient = _clients[index];
                  _clientToEdit = ChangeableClient.fromClient(_clients[index]);
                  await _onClientTap();
                  _setState(() {});
                },
              );
            })),
    Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            IconButton(
                onPressed: () {
                  _createAddUserDialog(_context());
                },
                icon: const Icon(Icons.add)),
            IconButton(onPressed: () {}, icon: const Icon(Icons.remove))
          ],
        ))
  ]);
}

Future<void> _onClientTap() async {
  if (_stages.isEmpty) {
    await searchStages(_stages);
  }

  var res = await connection.query("SELECT * FROM  search_orders(@client_id)",
      substitutionValues: {"client_id": _selectedClient.id});

  _orders.clear();
  for (final row in res) {
    _orders.add(Order(row[0], row[1], row[2], row[3], row[4], row[5]));
  }
}

void _createAddUserDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        _clientToAdd = ChangeableClient();
        return AlertDialog(
          title: const Text("Добавить нового клиента"),
          content: Column(children: [
            Expanded(
                child: TextField(
              decoration: const InputDecoration(hintText: "Введите имя"),
              onChanged: (str) => _clientToAdd.firstName = str,
            )),
            Expanded(
                child: TextField(
              decoration: const InputDecoration(hintText: "Введите отчество"),
              onChanged: (str) => _clientToAdd.middleName = str,
            )),
            Expanded(
                child: TextField(
              decoration: const InputDecoration(hintText: "Введите фамилию"),
              onChanged: (str) => _clientToAdd.lastName = str,
            )),
            Expanded(
                child: TextField(
              expands: false,
              decoration:
                  const InputDecoration(hintText: "Введите номер телефона"),
              onChanged: (str) => _clientToAdd.phone = str,
            )),
          ]),
          actions: [
            TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text("Отмена")),
            TextButton(
                onPressed: () {
                  addClient(_clientToAdd);
                  Navigator.of(context).pop();
                },
                child: const Text("Создать"))
          ],
          actionsAlignment: MainAxisAlignment.spaceAround,
        );
      });
}

Column _scdColumn() {
  final tc1 = TextEditingController();
  final tc2 = TextEditingController();
  final tc3 = TextEditingController();
  final tc4 = TextEditingController();
  return Column(children: [
    Expanded(
        child: Container(
            color: Colors.amberAccent,
            child: ListView(
              children: [
                ListTile(
                    title: TextField(
                        enabled: true,
                        controller: tc1,
                        onChanged: (val) => _clientToEdit.firstName = val,
                        decoration: InputDecoration(
                            hintText: _selectedClient.firstName)),
                    subtitle: const Text("Имя")),
                ListTile(
                    title: TextField(
                        enabled: true,
                        controller: tc2,
                        onChanged: (val) => _clientToEdit.lastName = val,
                        decoration: InputDecoration(
                            hintText: _selectedClient.lastName)),
                    subtitle: const Text("Фамилия")),
                ListTile(
                    title: TextField(
                        enabled: true,
                        controller: tc3,
                        onChanged: (val) => _clientToEdit.middleName = val,
                        decoration: InputDecoration(
                            hintText: _selectedClient.middleName)),
                    subtitle: const Text("Отчество")),
                ListTile(
                    title: TextField(
                        enabled: true,
                        controller: tc4,
                        onChanged: (val) => _clientToEdit.phone = val,
                        decoration:
                            InputDecoration(hintText: _selectedClient.phone)),
                    subtitle: const Text("Телефон"))
              ],
            ))),
    Container(
        color: Colors.amber,
        child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
          IconButton(
              onPressed: () async {
                await saveClientChanges(_clientToEdit);
                await searchClients(_clientToEdit.phone as String, _clients);
                tc1.clear();
                tc2.clear();
                tc3.clear();
                tc4.clear();
                _selectedClient = _clients[0];
                _setState(() {});
              },
              icon: const Icon(Icons.save))
        ])),
    Expanded(
        child: Container(
      color: Colors.amberAccent,
      child: ListView.builder(
        itemCount: _orders.length,
        itemBuilder: (BuildContext context, int index) {
          return ListTile(
            title: Text(_orders[index].orderTime.toLocal().toString()),
            enabled: true,
            onTap: () async {
              _selectedOrder = _orders[index];
              await _onOrderTap();
              _setState(() {});
            },
          );
        },
      ),
    )),
    Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            IconButton(
                onPressed: () => _createAddOrderDialog(_context()),
                icon: const Icon(Icons.add)),
            // IconButton(onPressed: () {}, icon: Icon(Icons.remove))
          ],
        ))
  ]);
}

void _createAddOrderDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        List<Substance> selectedSubs = [];
        final List<Substance> substances = [];
        final List<int> count = [1];

        return StatefulBuilder(builder: (context, setState) {
          return AlertDialog(
            title: const Center(child: Text("Добавить новый заказ")),
            content: Row(children: [
              SizedBox(
                  width: 500,
                  child: _searchSubstancesColumnForPop(
                      substances, setState, count, selectedSubs)),
              SizedBox(
                  width: 500,
                  child:
                      _selectedSubstancesColumnForPop(selectedSubs, setState))
            ]),
            actions: [
              TextButton(
                  onPressed: () => Navigator.of(context).pop(),
                  child: const Text("Отмена")),
              TextButton(
                  onPressed: () {
                    addOrder(selectedSubs, _selectedClient);
                    Navigator.of(context).pop();
                  },
                  child: const Text("Создать"))
            ],
            actionsAlignment: MainAxisAlignment.spaceBetween,
          );
        });
      });
}

Column _searchSubstancesColumnForPop(
    List<Substance> subs,
    void Function(void Function()) f,
    List<int> count,
    List<Substance> selectedSubs) {
  return Column(children: [
    Row(
      children: [
        Expanded(
            child: TextField(
                decoration:
                    const InputDecoration(hintText: "Введите лекарство..."),
                onChanged: (name) => f(() {
                      searchSubstances(name, subs);
                    }))),
        const Icon(Icons.search, color: Colors.white)
      ],
    ),
    Row(
      children: [
        Expanded(
            child: TextField(
                decoration:
                    const InputDecoration(hintText: "Введите количество..."),
                onChanged: (name) {
                  count[0] = int.parse(name);
                })),
        const Icon(Icons.add_circle_outline, color: Colors.white)
      ],
    ),
    Expanded(
        child: ListView.builder(
            itemCount: subs.length,
            itemBuilder: (BuildContext b, int index) {
              return ListTile(
                  title: Text(
                      "${subs[index].name}, в наличии ${subs[index].count} шт."),
                  onTap: () {
                    f(() {
                      selectedSubs.add(Substance(subs[index].id,
                          subs[index].name, -1, -1, count[0], "-1"));
                    });
                  });
            }))
  ]);
}

Column _selectedSubstancesColumnForPop(
  List<Substance> selectedSubs,
  void Function(void Function()) f,
) {
  return Column(children: [
    Expanded(
        child: Container(
      color: Colors.amberAccent,
      child: ListView.builder(
        itemCount: selectedSubs.length,
        itemBuilder: (BuildContext context, int index) {
          return ListTile(
            title: Text(
                "${selectedSubs[index].name}, ${selectedSubs[index].count} шт."),
            onTap: () {
              f(() => selectedSubs.removeAt(index));
            },
          );
        },
      ),
    )),
  ]);
}

Future<void> _onOrderTap() async {
  var res = await connection.query(
      "SELECT * FROM  search_client_order_sub_rel(@order_id)",
      substitutionValues: {"order_id": _selectedOrder.id});

  _subsInOrder.clear();

  for (final row in res) {
    _subsInOrder.add(OrderSub(row[0], row[1]));
  }
}

Column _trdColumn() {
  return Column(children: [
    Expanded(
        child: Container(
            color: Colors.amberAccent,
            child: ListView(
              children: [
                ListTile(
                    title: TextField(
                        enabled: false,
                        decoration: InputDecoration(
                            hintText: _stages[_selectedOrder.stage])),
                    subtitle: const Text("Стадия")),
                ListTile(
                    title: TextField(
                        enabled: false,
                        decoration: InputDecoration(
                            hintText:
                                _selectedOrder.orderTime.toLocal().toString())),
                    subtitle: const Text("Время заказа")),
                ListTile(
                    title: TextField(
                        enabled: false,
                        decoration: InputDecoration(
                            hintText: _selectedOrder.readyTime == null
                                ? ""
                                : _selectedOrder.readyTime
                                    ?.toLocal()
                                    .toString())),
                    subtitle: const Text("Время готовности")),
                ListTile(
                    title: TextField(
                        enabled: false,
                        decoration: InputDecoration(
                            hintText: _selectedOrder.readyTime == null
                                ? ""
                                : _selectedOrder.receiveTime
                                    ?.toLocal()
                                    .toString())),
                    subtitle: const Text("время получения"))
              ],
            ))),
    Expanded(
        child: Container(
      color: Colors.amberAccent,
      child: ListView.builder(
        itemCount: _subsInOrder.length,
        itemBuilder: (BuildContext context, int index) {
          return Text(
              "${_subsInOrder[index].subName}, ${_subsInOrder[index].count} шт.");
        },
      ),
    )),
    Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            IconButton(
                onPressed: () {
                  makeOrderReceived(_selectedOrder);
                },
                icon: const Icon(Icons.verified_outlined))
          ],
        ))
  ]);
}
