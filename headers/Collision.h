#ifndef COLLISION_H
#define COLLISION_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);

	private:

		static inline float Mag(const Vec2& p) {
			return std::sqrt(p.x * p.x + p.y * p.y);
		}

		static inline Vec2 Norm(const Vec2& p) {
			return p * (1.f / Mag(p));
		}

		static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x * b.x + a.y * b.y;
		}

		static inline Vec2 Rotate(const Vec2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};








#endif