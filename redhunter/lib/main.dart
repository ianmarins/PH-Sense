import 'package:flutter/material.dart';

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'redhunter',
      theme: new ThemeData(
        primaryColorBrightness: Brightness.light,
        primarySwatch: Colors.blue,
      ),
      home: new HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {

  Widget _buildAppBar(){
    return new AppBar(
      backgroundColor: Colors.transparent,
      elevation: 0.0,
      leading: new IconButton(
        icon: new Icon(
          Icons.person,
          color: Colors.grey,
          size: 40.0,
        ),
        onPressed: (){
          // TODO:
        },
      ),
      title: new Text("Logo Aqui",),
      actions: <Widget>[
        new IconButton(
        icon: new Icon(
          Icons.chat_bubble,
          color: Colors.grey,
          size: 40.0,
        ),
        onPressed: (){
          // TODO:
        },
      ),
      ],
    );
  }

  Widget _buildBottomBar(){
    return BottomAppBar(
      color: Colors.transparent,
      elevation: 0.0,
      child: new Padding(
        padding: const EdgeInsets.all(16.0),
        child: new Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: <Widget>[
              new RoundIconButton.large(
                icon: Icons.clear,
                iconColor: Colors.red,
                onPressed: (){

                },
              ),
              new RoundIconButton.small(
                icon: Icons.refresh,
                iconColor: Colors.blue,
                onPressed: (){

                },
              ),
              new RoundIconButton.large(
                icon: Icons.favorite,
                iconColor: Colors.green,
                onPressed: (){

                },
              ),
            ],
          ),
        ),
    );
  }


  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: _buildAppBar(),
      body: new Center(),
      bottomNavigationBar: _buildBottomBar(),
    );
  }
}

class RoundIconButton extends StatelessWidget {
  final IconData icon;
  final Color iconColor;
  final double size;
  final VoidCallback onPressed;

  RoundIconButton.large({
    this.icon,
    this.iconColor,
    this.onPressed,
  }) : size = 60.0;

    RoundIconButton.small({
    this.icon,
    this.iconColor,
    this.onPressed,
  }) : size = 40.0;

  RoundIconButton({
    this.icon,
    this.iconColor,
    this.onPressed,
    this.size
  });

  @override
  Widget build(BuildContext context) {
    return new Container(
      width: size,
      height: size,
      decoration: new BoxDecoration(
        shape: BoxShape.circle,
        color: Colors.white,
        boxShadow: [
          new BoxShadow(
            color: const Color(0x11000000),
            blurRadius: 10.0,
          ),
        ],
      ),
      child: new RawMaterialButton(
        shape: new CircleBorder(),
        elevation: 0.0,
        child: new Icon(
          icon,
          color: iconColor,
        ),
        onPressed: onPressed,
      ),
    );
  }
}