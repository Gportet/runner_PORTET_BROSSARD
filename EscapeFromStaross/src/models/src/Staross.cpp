#include "../header/Staross.hpp"

Staross::Staross(sf::RenderWindow& w, Camera& c, Player& p) : window(w), camera(c), player(p), m_texture()
{
    if (!m_texture.loadFromFile("Assets/Textures/staross.png")) {
        throw std::runtime_error("Failed to load staross texture");
    }
	m_speed = sf::Vector2f(11,0);
    randomX(0, 5);
    updatePositionDestination();
    init();
}

void Staross::init() {

    float yMaxWindow = window.getSize().y;
    float spaceBetween = yMaxWindow / 7;
    sf::Vector2f pos = sf::Vector2f(10, 30);
    m_sprites.clear();
    m_hitboxes.clear();
    for (size_t i = 0; i < 5; i++)
    {
        sf::Sprite s = makeStar(pos, 40.f, 75.f, 7);

        // --- Ajuster ces valeurs pour agrandir/rétrécir la hitbox ---
        constexpr float HITBOX_SCALE = 0.40f;   // multiplicateur par rapport à la plus petite dimension du sprite
        constexpr float HITBOX_PADDING = 5.0f;  // ajout fixe en pixels
   

        sf::FloatRect g = s.getGlobalBounds();
        float radius = std::min(g.size.x, g.size.y) * HITBOX_SCALE + HITBOX_PADDING;
        sf::CircleShape hb(radius);
        hb.setOrigin(sf::Vector2f(radius, radius));
        hb.setPosition(s.getPosition());

        hb.setFillColor(sf::Color::Transparent);
        // hb.setOutlineColor(sf::Color::Red); hb.setOutlineThickness(1.f); // debug

        m_sprites.push_back(std::move(s));
        m_hitboxes.push_back(std::move(hb));

        pos.y += spaceBetween;
    }
}

void Staross::reset() {
    m_sprites.clear();
    m_hitboxes.clear();
    init();
}

sf::Sprite Staross::makeStar(sf::Vector2f origin, float radiusCenter, float radiusOut, int points )
{
    sf::Sprite star = sf::Sprite(m_texture);

    const float pi = 3.14159265f;
    for (int i = 0; i < points * 2; ++i)
    {
        float angle = i * pi / points - pi / 2; // -pi/2 pour orienter vers le haut
        float radius = (i % 2 == 0) ? radiusCenter : radiusOut;
        sf::Vector2f point(std::cos(angle) * radius, std::sin(angle) * radius);
        (void)point; // calcul conservé si besoin pour dessiner une forme personnalisée plus tard
    }
    // Style

    // Centre l'origine sur le centre du sprite (SFML3 compatible)
    // getLocalBounds().getCenter() existe ; utiliser le calcul explicite si souhaité
    sf::FloatRect lb = star.getLocalBounds();
    star.setOrigin(sf::Vector2f(lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f));

    // Taille par défaut (1.0 = texture origine)
    constexpr float STAR_SCALE = 1.0f;
    star.setScale(sf::Vector2f{ STAR_SCALE, STAR_SCALE });

    // Position initiale
    star.setPosition(origin);
    return star;
}


void Staross::rotate()
{
    for (auto& sprite : m_sprites)
    {
        sprite.rotate(sf::degrees(m_speed.x));
    }
    // Les hitboxes circulaires ne changent pas avec la rotation (approximation),
    // donc on ne les tourne pas. Si tu veux une hitbox orientée, utiliser ConvexShape.
}


void Staross::update() {
    move();
    rotate();
}

void Staross::draw() {

	for (auto& sprite : m_sprites)
	{
		window.draw(sprite);
	}

	// Pour debug, dessiner les hitboxes (elles sont transparentes par défaut)
	for (const auto& hb : m_hitboxes)
	{
		window.draw(hb);
	}
}

void Staross::randomX(float min, float max)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    float r = dist(rng);
    //permet au aller-retour de ne pas etre trop petit
    abs(m_randomPercentage - r) < 10 ? r += 10*m_direction : r;
    r >= 45 ? r = 45 : r;
    m_randomPercentage = r;
}

void Staross::updatePositionDestination() {
    sf::View view = camera.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - size.x / 2.f;

    float pos = left + (m_randomPercentage / 100.f) * size.x;
    m_posDestination = pos;
}

void Staross::move()
{
    updatePositionDestination();
    if (m_sprites.empty()) return;

    float xInit = m_sprites[0].getPosition().x;

    if ((m_direction > 0 && xInit >= m_posDestination) ||
        (m_direction < 0 && xInit <= m_posDestination))
    {
        randomX(35, 40);
        updatePositionDestination();
        m_direction = (xInit > m_posDestination) ? -1.f : 1.f;
    }
    for (size_t i = 0; i < m_sprites.size(); ++i)
    {
        auto& sprite = m_sprites[i];
        sf::Vector2f pos = sprite.getPosition();

        m_direction < 0 ? m_speed = sf::Vector2f(2, 0) : m_speed = sf::Vector2f(12,0);
        float step = m_speed.x * m_direction;
        pos.x += step;
        sprite.setPosition(pos);

        // Synchronise la hitbox correspondante
        if (i < m_hitboxes.size()) {
            m_hitboxes[i].setPosition(pos);
        }
    }
}



