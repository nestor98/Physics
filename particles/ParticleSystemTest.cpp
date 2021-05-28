
#pragma warning( disable : 4244 ) 
#include "ParticleSystemTest.h"
#include "../utils/resource.h"

ps::ParticleSystemTest::ParticleSystemTest(sf::RenderWindow& _window, const sf::Texture& t) 
	: pSettings(), pSystem(pSettings), window(_window), cam(_window.getView())
{
	pSystem.setTexture(t);
}


ps::ParticleSystemTest::ParticleSystemTest(sf::RenderWindow& _window, const sf::Texture& t, const sf::IntRect& r)
    : pSettings(), pSystem(pSettings), window(_window), cam(_window.getView())
{
    pSystem.setTexture(t, r);
}

void ps::ParticleSystemTest::loop()
{
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {

        captureEvents();
        dT = deltaClock.restart();
        update();
        draw();
    }

    ImGui::SFML::Shutdown();
}

void ps::ParticleSystemTest::draw() const
{
    window.clear();

    window.draw(pSystem);
    ImGui::SFML::Render(window);

    window.display();
}

void ps::ParticleSystemTest::update()
{
    pSystem.update(dT);
    ImGui::SFML::Update(window, dT);

    // Input:
    ImGui::Begin("Settings!");
    bool pressed = ImGui::Button("Cycle preset");
    if (pressed) loadNextPSettings();
    else {
        if (ImGui::Button(pSettings.gravity ? "Gravity ON" : "Gravity OFF")) pSettings.gravity = !pSettings.gravity;
        ImGui::DragFloat("LifeTime", &ttl, 0.05f, 0.0f, 5.0f);
        ImGui::DragFloat("Size Ini", &pSettings.sizeIni, 0.10f, 0.0f, 500.0f);
        ImGui::DragFloat("Size End", &pSettings.sizeEnd, 0.10f, 0.0f, 500.0f);
        ImGui::DragFloat2("Vel", vel, 5, -1000, 1000);
        ImGui::DragFloat2("Negative vel var [x,y]", &vel[2], 5, 0, 1000);
        ImGui::DragFloat2("Positive vel var [x,y]", &vel[4], 5, 0, 1000);
        ImGui::ColorEdit4("Color Ini", colIni);
        ImGui::ColorEdit4("Color End", colEnd);
    }
    ImGui::End();

    // Update settings:
    if (!pressed) updateSettings();
    //pSystem.setParticleSettings(pSettings);
}

void ps::ParticleSystemTest::captureEvents() 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        cam.moveByMouse(sf::Mouse::getPosition());
        window.setView(cam);
    }
    else {
        cam.resetDrag();
    }
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }  
        else if (event.type == sf::Event::KeyPressed && event.key.control && event.key.code == sf::Keyboard::S) 
        { // Save
            if (!Resources::getInstance().savePSettings(pSettings)) std::cerr << "Error saving particle settings\n";
            else std::cout << "Preset saved\n";
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) { // Zoom
                float factor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
                cam.zoom(factor);
                window.setView(cam);
            }
        }

    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //std::cout << "emiting at " << utils::mousePosition2f(window) << "\n";
        pSystem.emit(utils::mousePosition2f(window));
    }


}

void ps::ParticleSystemTest::loadNextPSettings()
{
    auto& rs = Resources::getInstance();
    const auto& presets = rs.getPSystemPresets();
    if (presets.empty()) return;
    currentPreset = (currentPreset + 1) % presets.size();
    pSettings = presets[currentPreset];
    updateVars();
}

void ps::ParticleSystemTest::updateVars()
{
    ttl = pSettings.ttl.asSeconds();
    vel[0] = pSettings.vel.x;
    vel[1] = pSettings.vel.y;
    vel[2] = pSettings.velVarNeg.x;
    vel[3] = pSettings.velVarNeg.y;
    vel[4] = pSettings.velVarPos.x;
    vel[5] = pSettings.velVarPos.y;

    colIni[0] = pSettings.colorIni.r;
    colIni[1] = pSettings.colorIni.g;
    colIni[2] = pSettings.colorIni.b;
    colIni[3] = pSettings.alphaIni;

    colEnd[0] = pSettings.colorEnd.r;
    colEnd[1] = pSettings.colorEnd.g;
    colEnd[2] = pSettings.colorEnd.b;
    colEnd[3] = pSettings.alphaEnd;

    for (int i = 0; i < 4; i++) {
        colIni[i] /= 255.0f;
        colEnd[i] /= 255.0f;
    }
}


void ps::ParticleSystemTest::updateSettings() {
    pSettings.ttl = sf::seconds(ttl);
    pSettings.vel.x = vel[0];
    pSettings.vel.y = vel[1];
    pSettings.velVarNeg.x = vel[2];
    pSettings.velVarNeg.y = vel[3];
    pSettings.velVarPos.x = vel[4];
    pSettings.velVarPos.y = vel[5];

    sf::Uint8 cI[4], cE[4];
    for (int i = 0; i < 4; i++) cI[i] = 255 * colIni[i];
    for (int i = 0; i < 4; i++) cE[i] = 255 * colEnd[i];
    pSettings.colorIni = sf::Color(cI[0], cI[1], cI[2]);
    pSettings.colorEnd = sf::Color(cE[0], cE[1], cE[2]);
    //std::cout << pSettings.colorEnd << " " << pSettings.colorIni << "\n";
    pSettings.alphaIni = cI[3];
    pSettings.alphaEnd = cE[3];
}
