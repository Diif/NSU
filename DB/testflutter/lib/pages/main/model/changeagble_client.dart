import 'package:testflutter/pages/main/model/client.dart';

class ChangeableClient{
  int? id;
  String? firstName;
  String? middleName;
  String? lastName;
  String? phone;

  ChangeableClient();

  ChangeableClient.fromClient(Client client){
    id = client.id;
    firstName = client.firstName;
    middleName = client.middleName;
    lastName = client.lastName;
    phone = client.phone;
  }

}