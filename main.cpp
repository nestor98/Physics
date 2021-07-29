#include "utils/resource.h"
#include "particles/ParticleSystemTest.h"

 
void testRNG(long N_TESTS = 10000000) {
    int min = 0, max = 10;
    float avg1, avg = 0;
    sf::Clock c;
    // Test 1:
    c.restart();
    sf::Time ini = c.getElapsedTime();
    for (int i = 0; i < N_TESTS; i++) {
        avg += float(rng::rand(min, max));
    }
    sf::Time t1 = c.getElapsedTime() - ini;
    avg1 = avg / float(N_TESTS);
    // Test 2:
    avg = 0;
    ini = c.getElapsedTime();
    for (int i = 0; i < N_TESTS; i++) {
        avg += float(rng::randWithIntDis(min, max));
    }
    sf::Time t2 = c.getElapsedTime() - ini;
    avg /= float(N_TESTS);
    std::cout << "----------------------Method 1:\n";
    std::cout << t1.asSeconds() << " s, Between " << min << " and " << max << ", "
        << N_TESTS << " avg = " << avg1 << " (expected -> " << float(max+min)/2.0<< ")\n";
    std::cout << "----------------------Method 2:\n";
    std::cout << t2.asSeconds() << " s, Between " << min << " and " << max << ", "
        << N_TESTS << " avg = " << avg << " (expected -> " << float(max + min) / 2.0 << ")\n";
}

void testIMGUI() {

    sf::RenderWindow window(sf::VideoMode(1600, 900), "I <3 particles");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // position
        float pos[2];
        ImGui::Begin("Hello, world!");
        ImGui::DragFloat2("Position", pos, 1, 0, 200);
        ImGui::End();
        shape.setPosition(pos[0], pos[1]);

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void particlesTest() {
    auto& rcs = Resources::getInstance(); // init resources

    sf::RenderWindow window(sf::VideoMode(1600, 900), "I <3 particles");
    window.setFramerateLimit(60);

    auto idx = Resources::TextureIdx::smoke;
    ps::ParticleSystemTest psTest(window, rcs.getTexture(idx), rcs.getIntRects(idx)[0]);
    psTest.loop();
}


int main() {
    //testRNG(); //testIMGUI(); // particlesTest()

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Orbits");
    window.setFramerateLimit(60);
    Orbit orbitApp(window, 2000, 200, 6);
    orbitApp.loop();
    
    return 0;
}
