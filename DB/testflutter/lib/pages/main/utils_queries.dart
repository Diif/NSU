import 'package:flutter/cupertino.dart';
import 'package:postgres/postgres.dart';
import 'package:testflutter/pages/main/model/changeable_substance.dart';
import 'package:testflutter/pages/main/model/changeable_supply_order.dart';
import 'package:testflutter/pages/main/model/changeable_tech.dart';
import 'package:testflutter/pages/main/model/order.dart';
import 'package:testflutter/pages/main/model/supply.dart';
import 'package:testflutter/pages/main/model/supply_order.dart';
import 'package:testflutter/pages/main/model/tech_with_sub.dart';
import 'package:testflutter/pages/main/queries/p_query.dart';

import 'model/changeagble_client.dart';
import 'model/client.dart';
import 'model/substance.dart';
import 'model/tech_comp_rel.dart';
import 'sub_section.dart';

late final PostgreSQLConnection _connection;

get connection => _connection;

void init(PostgreSQLConnection connection) {
  _connection = connection;
}

Future<void> searchCategories(final categories) async {
  var res = await connection.query("SELECT * FROM  categories");
  for (final row in res) {
    categories[row[0]] = row[1];
  }
}

Future<void> searchSupplyOrders(List<SupplyOrder> orders) async {
  var res = await connection.query("SELECT * FROM  search_supply_orders()");
  for (final row in res) {
    orders.add(SupplyOrder(row[0], row[1], row[2], row[3], row[4], row[5]));
  }
}

Future<void> searchSubstances(
    String name, final List<Substance> substances) async {
  var res = await connection.query("SELECT * FROM  search_substances(@name)",
      substitutionValues: {"name": name});

  substances.clear();
  for (final row in res) {
    substances.add(Substance(row[0], row[1], row[2], row[3], row[4], row[5]));
  }
}

Future<TechWithSub> searchTech(
    String subName) async {
  var res = await connection.query("SELECT * FROM  search_tech(@name)",
      substitutionValues: {"name": subName});

  var forReturn = TechWithSub(-1, -1, "", "", Duration.zero, -1);
  for (final row in res) {
    forReturn = TechWithSub(row[0], row[1], row[2], row[3], row[4], row[5]);
    break;
  }
  return forReturn;
}

Future<void> searchTechCompRel(final List<TechCompRel> rels, int techId) async {
  var res = await connection.query("SELECT * FROM  search_tech_comp_rel(@id)",
      substitutionValues: {"id": techId});

  for (final row in res) {
    rels.add(TechCompRel(row[0], row[1], row[2]));
  }
}



Future<void> searchStages(final Map<int, String> stages) async {
  var res = await connection.query("SELECT * FROM  client_order_stages");
  for (final row in res) {
    stages[row[0]] = row[1];
  }
}

Future<void> searchClients(String phone, final List<Client> clients) async {
  var res = await connection.query("SELECT * FROM  search_clients(@phone)",
      substitutionValues: {"phone": phone});
  clients.clear();

  for (final row in res) {
    clients.add(Client(row[0], row[1], row[2], row[3], row[4]));
  }
}

Future<void> makeOrderReceived(Order selectedOrder) async {
  if (selectedOrder.id == -1) {
    return;
  }

  await connection.query("CALL move_order_to_received_stage(@order_id)",
      substitutionValues: {
        "order_id": selectedOrder.id,
      });
}

Future<void> saveSubChanges(ChangeableSubstance sub) async{
  await connection.query("CALL update_sub(@id, @name, @cat_name,@crit, @price)",
      substitutionValues: {
        "id": sub.id,
        "name": sub.name,
        "cat_name": sub.categoryName,
        "crit": sub.critCount,
        "price": sub.pricePcs
      });
}

Future<void> saveTechChanges(ChangeableTech tech) async{
  await connection.query("CALL update_tech(@id, @sub_name, @desc ,@time, @count)",
      substitutionValues: {
        "id": tech.id,
        "sub_name": tech.medicineName,
        "desc": tech.description,
        "time": tech.creationTime.toString(),
        "count": tech.medCount
      });
}

Future<void> saveRelTechChanges(int techId, final List<TechCompRel> selectedRels) async{
  if (techId == -1) {
    return;
  }

  List<int> subId = [];
  List<int> subCount = [];

  print(techId);
  print(subId);
  print(subCount);
  for (var element in selectedRels) {
    subId.add(element.subId);
    subCount.add(element.count);
  }
  await connection.query("CALL update_tech_rels(@id, @subs, @sub_count)",
      substitutionValues: {
        "id": techId,
        "subs": subId,
        "sub_count": subCount
      });
}

Future<void> saveClientChanges(ChangeableClient client) async{
  await connection.query("CALL update_client(@id, @fst_name, @middle_name, @last_name, @phone)",
      substitutionValues: {
        "id": client.id,
        "fst_name": client.firstName,
        "middle_name": client.middleName,
        "last_name": client.lastName,
        "phone": client.phone,
      });
}

Future<void> addClient(ChangeableClient clientToAdd) async {
  if (clientToAdd.phone == null ||
      clientToAdd.firstName == null ||
      clientToAdd.middleName == null ||
      clientToAdd.lastName == null) {
    return;
  }

  await connection.query("CALL insert_client(@name, @middle, @last, @phone)",
      substitutionValues: {
        "name": clientToAdd.firstName,
        "middle": clientToAdd.middleName,
        "last": clientToAdd.lastName,
        "phone": clientToAdd.phone,
      });
}

Future<void> addOrder(final List<Substance> subs, Client selectedClient) async {
  if (subs.isEmpty || selectedClient.id == -1) {
    return;
  }

  List<int> subId = [];
  List<int> subCount = [];

  for (var element in subs) {
    subId.add(element.id);
    subCount.add(element.count);
  }

  await connection.query(
      "CALL create_order_wrapper(@client_id, @substances_to_add, @sub_count)",
      substitutionValues: {
        "client_id": selectedClient.id,
        "substances_to_add": subId,
        "sub_count": subCount
      });
}

Future<void> addSub(ChangeableSubstance sub) async{
  await connection.query("CALL create_sub(@name, @category, @crit, @price)",
      substitutionValues: {
        "name": sub.name,
        "category": sub.categoryName,
        "crit": sub.critCount,
        "price": sub.pricePcs
      });
}

Future<void> addTech(ChangeableTech tech, List<TechCompRel> selectedRels) async{
  if (selectedRels.isEmpty || tech.id == -1) {
    return;
  }

  List<int> subId = [];
  List<int> subCount = [];

  for (var element in selectedRels) {
    subId.add(element.subId);
    subCount.add(element.count);
  }


  await connection.query("CALL create_tech(@med_name,@desc, @time, @count, @substances_to_add, @sub_count)",
      substitutionValues: {
        "med_name": tech.medicineName,
        "desc": tech.description,
        "time": tech.creationTime.toString(),
        "count": tech.medCount,
        "substances_to_add": subId,
        "sub_count": subCount
      });
}

Future<void> addSupplyOrder(ChangeableSupplyOrder order) async{
  await connection.query("CALL create_supply_order(@sub_name, @count)",
      substitutionValues: {
        "sub_name": order.subName,
        "count": order.countToReceive
      });
}

Future<void> addSupply(int orderId, int count) async{
  await connection.query("CALL create_supply(@order_id, @count)",
      substitutionValues: {
        "order_id": orderId,
        "count": count
      });
}

Future<void> removeTech(TechWithSub tech) async{
  await connection.query("CALL remove_tech(@id)",
      substitutionValues: {
        "id": tech.id
      });
}

Future<List<TableRow>> executeQuery(PQuery q, Map<String, String> args) async{
  var res = await connection.query(q.body,
      substitutionValues: args);

  List<TableRow> rows = [];


  for (final row in res){
    List<Text> buf = [];
    for (final col in row){
      buf.add(Text(col.toString()));
    }
    rows.add(TableRow(children: buf));
  }

  return rows;

}