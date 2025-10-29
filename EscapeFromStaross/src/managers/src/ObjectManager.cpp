#include "../header/ObjectManager.hpp"

ObjectManager::ObjectManager(sf::RenderWindow& window, Camera& camera) : m_window(window), m_camera(camera)
{

}

void ObjectManager::update()
{
	for (auto& c : cailloux) {
		c->update();
	}
	checkCollisions();
}


void ObjectManager::draw()
{
	for (auto& c : cailloux)
		c->draw(m_window);
}

void ObjectManager::checkCollisions()
{
    sf::View view = m_camera.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float right = center.x + size.x / 2.f;
	//check collision des projectiles
    for (size_t i = 0; i < cailloux.size(); i++)
    {
        for (size_t i = 0; i < cailloux.size(); i++)
        {
            // collision avec obstacles
            for (auto& o : obstacles)
            {
                if (cailloux[i]->getGlobalBounds().findIntersection(o->getGlobalBounds()))
                {
                    cailloux[i]->collision();
                }
            }

            // collision avec mur droit
            sf::FloatRect bounds = cailloux[i]->getGlobalBounds();
            if (bounds.position.x + bounds.size.x >= right)
            {
                cailloux[i]->collision();
            }

            // suppression si le timer est �coul�
            if (cailloux[i]->shouldBeRemoved())
            {
                cailloux.erase(cailloux.begin() + i);
                --i;
            }
        }
    }
}

void ObjectManager::addCailloux(std::unique_ptr<Cailloux> c)
{
	cailloux.push_back(std::move(c));
}