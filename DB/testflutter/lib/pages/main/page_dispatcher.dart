import 'dart:ffi';

import 'package:flutter/material.dart';
import 'package:postgres/postgres.dart';
import 'package:testflutter/pages/main/query_section.dart';
import 'package:testflutter/pages/main/sub_section.dart';
import 'package:testflutter/pages/main/model/changeagble_client.dart';
import 'package:testflutter/pages/main/model/client.dart';
import 'package:testflutter/pages/main/model/order.dart';
import 'package:testflutter/pages/main/model/substance.dart';
import 'package:testflutter/pages/main/main_section.dart';
import 'package:testflutter/pages/main/supply_section.dart';
import 'package:testflutter/pages/main/tech_section.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

import 'model/order_sub.dart';

enum Page { main, queries, supplies, techs, subs }

class PageDispatcher extends StatefulWidget {
  const PageDispatcher({Key? key}) : super(key: key);

  @override
  State<PageDispatcher> createState() {
    return _PageDispatcherState();
  }
}

class _PageDispatcherState extends State<PageDispatcher> {


  @override
  Widget build(BuildContext context) {
    return getCurrentPage();
  }

  var _curPage = Page.main;

  Widget getCurrentPage() {
    switch (_curPage) {
      case Page.main:
        return mainSection();
      case Page.queries:
        return querySection();
      case Page.supplies:
        return supplySection();
      case Page.subs:
        return subSection();
      case Page.techs:
        return techSection();
    }
  }

  Widget mainSection() {
    return Scaffold(
        appBar: getAppBar(),
        body: getMainSection(setState, () => context));
  }

  Widget querySection() {
    return Scaffold(
        appBar: getAppBar(),
        body: getQuerySection(setState, () => context));
  }

  Widget supplySection() {
    return Scaffold(
        appBar: getAppBar(),
        body: getSupplySection(setState, () => context));
  }

  Widget techSection() {
    return Scaffold(
        appBar: getAppBar(),
        body: getTechSection(setState, () => context));
  }

  Widget subSection() {
    return Scaffold(
        appBar: getAppBar(),
        body: getSubSection(setState, () => context));
  }

  AppBar getAppBar() {
    return AppBar(
      title: const Text("Аптека"),
      backgroundColor: Colors.amber,
      shadowColor: Colors.yellow,
      actions: [
        TextButton(
            onPressed: () {
              setState(() {
                _curPage = Page.main;
              });
            },
            child: const Text(style: TextStyle(color: Colors.white70), "Главная")),
        TextButton(
            onPressed: () {
              setState(() {
                _curPage = Page.queries;
              });
            },
            child: const Text(style: TextStyle(color: Colors.white70), "Запросы")),
        TextButton(
            onPressed: () {
              setState(() {
                _curPage = Page.supplies;
              });
            },
            child: const Text(style: TextStyle(color: Colors.white70), "Поставки")),
        TextButton(
            onPressed: () {
              setState(() {
                _curPage = Page.subs;
              });
            },
            child: const Text(style: TextStyle(color: Colors.white70), "Лекарства")),
        TextButton(
            onPressed: () {
              setState(() {
                _curPage = Page.techs;
              });
            },
            child: const Text(style: TextStyle(color: Colors.white70), "Технологии"))
      ],
    );
  }

}
