#include "../header/Staross.hpp"

Staross::Staross(sf::RenderWindow& w, Camera& c, Player& p) : window(w), camera(c), player(p), m_texture(), m_sprite(m_texture)
{
    if (!m_texture.loadFromFile("Assets/Textures/staross.png")) {
        throw std::runtime_error("Failed to load staross texture");
    }

	m_sprite = sf::Sprite(m_texture);
	m_sprite.setScale(sf::Vector2f(-3, 3));

	m_speed = sf::Vector2f(11,0);
    randomX(0, 5);
    updatePositionDestination();

    sf::FloatRect sb = m_sprite.getGlobalBounds();
	sf::FloatRect lb = m_sprite.getLocalBounds();
    m_sprite.setOrigin(sf::Vector2f(lb.size.x / 2, lb.size.y /2));

    m_hitbox.setSize(sf::Vector2f(sb.size.x, sb.size.y));
    m_hitbox.setOrigin(sf::Vector2f(sb.size.x / 2, sb.size.y / 2));

    m_hitbox.setFillColor(sf::Color(0, 0, 0, 0));
    m_hitbox.setOutlineColor(sf::Color::Red);     // contour rouge
    m_hitbox.setOutlineThickness(2.f);
    m_hitbox.setPosition(m_sprite.getPosition());


    init();

}

void Staross::init() {

    float yMaxWindow = window.getSize().y;
    //float spaceBetween = yMaxWindow / 7;
    sf::Vector2f pos = sf::Vector2f(10, 450);
	m_sprite.setPosition(pos);
}

void Staross::reset() {
    init();
}

sf::Sprite Staross::getSprite()
{
    return m_sprite;
}

//sf::Sprite Staross::makeStar(sf::Vector2f origin, float radiusCenter, float radiusOut, int points )
//{
//    sf::Sprite star = sf::Sprite(m_texture);
//
//    const float pi = 3.14159265f;
//    for (int i = 0; i < points * 2; ++i)
//    {
//        float angle = i * pi / points - pi / 2; // -pi/2 pour orienter vers le haut
//        float radius = (i % 2 == 0) ? radiusCenter : radiusOut;
//        sf::Vector2f point(std::cos(angle) * radius, std::sin(angle) * radius);
//        (void)point; // calcul conservé si besoin pour dessiner une forme personnalisée plus tard
//    }
//    // Style
//
//    // Centre l'origine sur le centre du sprite (SFML3 compatible)
//    // getLocalBounds().getCenter() existe ; utiliser le calcul explicite si souhaité
//    sf::FloatRect lb = star.getLocalBounds();
//    star.setOrigin(sf::Vector2f(lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f));
//
//    // Taille par défaut (1.0 = texture origine)
//    constexpr float STAR_SCALE = 1.0f;
//    star.setScale(sf::Vector2f{ STAR_SCALE, STAR_SCALE });
//
//    // Position initiale
//    star.setPosition(origin);
//    return star;
//}


//void Staross::rotate()
//{
//    for (auto& sprite : m_sprites)
//    {
//        sprite.rotate(sf::degrees(m_speed.x));
//    }
//    // Les hitboxes circulaires ne changent pas avec la rotation (approximation),
//    // donc on ne les tourne pas. Si tu veux une hitbox orientée, utiliser ConvexShape.
//}


void Staross::update() {
    move();

    //rotate();
}

void Staross::draw() {

	/*for (auto& sprite : m_sprites)
	{
		window.draw(sprite);
	}*/

    window.draw(m_sprite);


	// Pour debug, dessiner les hitboxes (elles sont transparentes par défaut)
	/*for (const auto& hb : m_hitboxes)
	{
		window.draw(hb);
	}*/
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
    m_hitbox.setPosition(m_sprite.getPosition());

    updatePositionDestination();

    // Position actuelle du sprite
    float xInit = m_sprite.getPosition().x;

    // Si on a atteint ou dépassé la destination, on recalcule une nouvelle cible
    if ((m_direction > 0 && xInit >= m_posDestination) ||
        (m_direction < 0 && xInit <= m_posDestination))
    {
        randomX(20, 30);
        updatePositionDestination();
        m_direction = (xInit > m_posDestination) ? -1.f : 1.f;
    }

    // Calcul du déplacement
    m_speed = (m_direction < 0) ? sf::Vector2f(2.f, 0.f) : sf::Vector2f(12.f, 0.f);
    float step = m_speed.x * m_direction;

    // Mise à jour de la position du sprite
    sf::Vector2f pos = m_sprite.getPosition();
    pos.x += step;
    m_sprite.setPosition(pos);
}





