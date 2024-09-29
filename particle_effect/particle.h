
//particle 抽象クラス

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
public:
	Particle(Float2 start_postion, Float2 acce, int life)
		:position(start_postion), acceleration(acce), life(life)
	{
	}
	virtual ~Particle() {}

private:
	Float2 position;
	Float2 acceleration;
	int life;
	int age = 0;

public:
	virtual void Update()
	{
		position += acceleration;  life--;
		age++;
		if (age > life) age = life;
		//age = std::min(++age, life);
	};
	virtual void Draw() = 0;

	void AddForce(Float2 force) { acceleration += force; }

	bool IsDead() { return age >= life; }

protected:
	Float2 GetPosition() { return position; }
	int GetLife() { return life; }
	int GetAge() { return age; }


};



#endif // !PARTICLE_H

