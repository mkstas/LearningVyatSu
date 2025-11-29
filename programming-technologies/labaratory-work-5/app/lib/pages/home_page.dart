import 'package:flutter/material.dart';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) => Scaffold(
    backgroundColor: const Color(0xFF292c3c),
    appBar: AppBar(
      title: const Text(
        'Макаров Станислав Алексеевич',
        style: TextStyle(
          color: Color(0xFFc6d0f5),
        ),
      ),
      backgroundColor: const Color(0xFF232634),
    ),
    body: Padding(
      padding: const EdgeInsets.all(12.0),
      child: ListView(
        children: [
          const Text(
            'Технологии программирования',
            style: TextStyle(
              fontSize: 24,
              fontWeight: FontWeight.w500,
              color: Color(0xFFc6d0f5),
            ),
          ),
          const SizedBox(height: 24),
          Container(
            margin: const EdgeInsets.only(bottom: 16),
            decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(12)),
              image: DecorationImage(
                image: AssetImage('assets/image1.jpg'),
                fit: BoxFit.cover,
              ),
            ),
            height: 200,
          ),
          Container(
            margin: const EdgeInsets.only(bottom: 16),
            decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(12)),
              image: DecorationImage(
                image: AssetImage('assets/image2.jpg'),
                fit: BoxFit.cover,
              ),
            ),
            height: 200,
          ),
          Container(
            margin: const EdgeInsets.only(bottom: 16),
            decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(12)),
              image: DecorationImage(
                image: AssetImage('assets/image3.jpg'),
                fit: BoxFit.cover,
              ),
            ),
            height: 200,
          ),
          Container(
            margin: const EdgeInsets.only(bottom: 16),
            decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(12)),
              image: DecorationImage(
                image: AssetImage('assets/image4.jpg'),
                fit: BoxFit.cover,
              ),
            ),
            height: 200,
          ),
          Container(
            margin: const EdgeInsets.only(bottom: 16),
            decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(12)),
              image: DecorationImage(
                image: AssetImage('assets/image5.jpg'),
                fit: BoxFit.cover,
              ),
            ),
            height: 200,
          ),
        ],
      ),
    ),
  );
}
