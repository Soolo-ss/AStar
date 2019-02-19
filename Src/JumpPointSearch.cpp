#include "JumpPointSearch.h"
#include "AStar.h"

namespace AStar
{
	std::vector<std::pair<int, AStarTileSharedPtr>> JumpPointSearch::GetJumpPoints(AStarTileSharedPtr current, AStarTileSharedPtr start, AStarTileSharedPtr end, AStarDirection parentDirection) 
	{
		start_ = start;
		end_ = end;

		std::vector<std::pair<int, AStarTileSharedPtr>> jumpPoints;

		int cost = 0;
		AStarTileSharedPtr jumpTile;

		std::vector<std::pair<AStarDirection, AStarTileSharedPtr>> neighbours = GetNeighbours(current, parentDirection);

		for (auto neighbour : neighbours)
		{
			jumpTile = Jump(current, neighbour.first, start, end);

			if (jumpTile != nullptr)
			{
				cost = GetJumpCost(current, neighbour.second, neighbour.first);
				jumpPoints.push_back(std::make_pair(cost, jumpTile));
			}
		}

		return jumpPoints;
	}

	int JumpPointSearch::GetJumpCost(AStarTileSharedPtr current, AStarTileSharedPtr target, AStarDirection direction)
	{
		int cost = 0;
		int abs = 0;

		if (IsDiagonal(direction))
		{
			abs = std::labs(target->GetX() - current->GetX());
			cost = 14 * abs;
		}
		else
		{
			if (IsHorizontal(direction))
			{
				abs = std::labs(target->GetX() - current->GetX());
				cost = 10 * abs;
			}
			else
			{
				abs = std::labs(target->GetZ() - current->GetZ());
				cost = 10 * abs;
			}
		}

		return cost;
	}

	/*
	���õݹ�ķ�ʽ����Jump �����׵���stack overflow 
	�޸ĳɻ��ڵ����ķ�ʽ
	*/
	AStarTileSharedPtr JumpPointSearch::Jump(AStarTileSharedPtr current,  AStarDirection direction, AStarTileSharedPtr start, AStarTileSharedPtr end)
	{
		AStarTileSharedPtr tile = Tile::CreateTileFromDirection(current, direction);

		//find a obstacle, give up jump
		if (!method_->CanMove(tile) || !method_->isExist(tile))
			return nullptr;

		if (*tile == *end)
			return tile;

		if (IsDiagonal(direction))
		{
			return JumpDiagonal(tile, direction);
		}
		else
		{
			return JumpOther(tile, direction);
		}

		return nullptr;
	}

	AStarTileSharedPtr JumpPointSearch::JumpDiagonal(AStarTileSharedPtr current, AStarDirection direction)
	{
		AStarTileSharedPtr firstTile = Tile::GetPool().acquire();
		AStarTileSharedPtr secondTile = Tile::GetPool().acquire();

		while (method_->isExist(current) && method_->CanMove(current))
		{
			firstTile->Copy(current);
			secondTile->Copy(current);
			if (isForcedTile(current, direction))
				return current;

			auto straightDirections = ResolveDiagonalDirection(direction);

			if (JumpOther(firstTile, straightDirections.first))
				return current;

			if (JumpOther(secondTile, straightDirections.second))
				return current;

			MoveTile(current, direction);
		}

		return nullptr;
	}

	AStarTileSharedPtr JumpPointSearch::JumpOther(AStarTileSharedPtr current, AStarDirection direction)
	{
		while (method_->isExist(current) && method_->CanMove(current))
		{
			if (isForcedTile(current, direction))
				return current;

			MoveTile(current, direction);
		}

		return nullptr;
	}

	bool JumpPointSearch::isForcedTile(AStarTileSharedPtr current, AStarDirection direction)
	{
		//�ж��Ƿ�Ϊ������
		if (*current == *end_)
			return true;

		if (IsDiagonal(direction))
		//����ֻ�ж��Ƿ��������forced ������ˮƽ�ʹ�ֱ������ж�
		{
			AStarDirection reverseDirection = ReverseDirection(direction);
			auto straightDirections = ResolveDiagonalDirection(reverseDirection);

			//???? ��Ҫ�жϵ㲻���ڵ������
			if ((!method_->CanMove(current, straightDirections.first)) || (!method_->CanMove(current, straightDirections.second)))
				return true;
		}
		else
		{
			if (IsHorizontal(direction))
			{
				if (!method_->CanMove(current, AStarDirection::Up))
				{
					//CanMove�������ƶ��� �п����ǵ㲻���ڻ����������ϰ�
					//�����ڵ������Ӱ��forcedTile�ж�
					if (method_->isExist(current, AStarDirection::Up))
						return true;
				}

				if (!method_->CanMove(current, AStarDirection::Down))
				{
					if (method_->isExist(current, AStarDirection::Down))
						return true;
				}
			}
			else
			{
				if (!method_->CanMove(current, AStarDirection::Left))
				{
					if (method_->isExist(current, AStarDirection::Left))
						return true;
				}

				if (!method_->CanMove(current, AStarDirection::Right))
				{
					if (method_->isExist(current, AStarDirection::Right))
						return true;
				}
			}
		}

		return false;
	}

	void JumpPointSearch::MoveTile(AStarTileSharedPtr current, AStarDirection direction)
	{
		current->AddDirectionOffset(direction);
	}

	std::vector<std::pair<AStarDirection, AStarTileSharedPtr>> JumpPointSearch::GetNeighbours(AStarTileSharedPtr current, AStarDirection parentDirection)
	{
		std::vector<std::pair<AStarDirection, AStarTileSharedPtr>> neighbours;


		AStarTileSharedPtr tile;
		//first node
		if (parentDirection == AStarDirection::None)
		{
			AStarDirection direction;
			for (int i = 0; i != static_cast<int>(AStarDirection::Max); ++i)
			{
				direction = static_cast<AStarDirection>(i);
				tile = Tile::CreateTileFromDirection(current, direction);

				if (method_->isExist(tile) && method_->CanMove(tile))
					neighbours.push_back(std::make_pair(direction, tile));
			}
		}
		else
		{ 
			if (IsDiagonal(parentDirection))
			{
				//ǰ�� 
				AStarTileSharedPtr frontTile = Tile::CreateTileFromDirection(current, parentDirection);

				if (method_->isExist(frontTile) && method_->CanMove(frontTile))
					neighbours.push_back(std::make_pair(parentDirection, frontTile));

				//��ǰ��
				AStarDirection leftFront = RotateDirection(parentDirection, 7);
				AStarTileSharedPtr leftFrontTile = Tile::CreateTileFromDirection(current, leftFront);
				if (method_->isExist(leftFrontTile) && method_->CanMove(leftFrontTile))
					neighbours.push_back(std::make_pair(leftFront, leftFrontTile));

				//��ǰ��
				AStarDirection rightFront = RotateDirection(parentDirection, 1);
				AStarTileSharedPtr rightFrontTile = Tile::CreateTileFromDirection(current, rightFront);
				if (method_->isExist(rightFrontTile) && method_->CanMove(rightFrontTile))
					neighbours.push_back(std::make_pair(rightFront, rightFrontTile));

				//����Һ��谭 ��ô���ҷ��ڵ�����ھ�
				AStarDirection rightBack = RotateDirection(parentDirection, 3);
				AStarTileSharedPtr rightBackTile = Tile::CreateTileFromDirection(current, rightBack);
				if (!method_->isExist(rightBackTile) || !method_->CanMove(rightBackTile))
				{
					AStarDirection right = RotateDirection(parentDirection, 2);
					AStarTileSharedPtr rightTile = Tile::CreateTileFromDirection(current, right);

					if (method_->isExist(rightTile) && method_->CanMove(rightTile))
					{
						neighbours.push_back(std::make_pair(right, rightTile));
					}
				}

				//�������谭�� ��ô���󷽽ڵ�����ھ�
				AStarDirection leftBack = RotateDirection(parentDirection, 5);
				AStarTileSharedPtr leftBackTile = Tile::CreateTileFromDirection(current, leftBack);
				if (!method_->isExist(leftBackTile) || !method_->CanMove(leftBackTile))
				{
					AStarDirection left = RotateDirection(parentDirection, 6);
					AStarTileSharedPtr leftTile = Tile::CreateTileFromDirection(current, left);

					if (method_->isExist(leftTile) && method_->CanMove(leftTile))
					{
						neighbours.push_back(std::make_pair(left, leftTile));
					}
				}
			}
			else
			{
				tile = Tile::CreateTileFromDirection(current, parentDirection);
			
				//ǰ��
				if (method_->isExist(tile) && method_->CanMove(tile))
					neighbours.push_back(std::make_pair(parentDirection, tile));

				//��
				AStarDirection left = RotateDirection(parentDirection, 6);
				AStarDirection leftFront = RotateDirection(parentDirection, 7);

				AStarTileSharedPtr leftTile = Tile::CreateTileFromDirection(current, left);
				AStarTileSharedPtr leftFrontTile = Tile::CreateTileFromDirection(current, leftFront);

				if (!method_->CanMove(leftTile) || !method_->isExist(leftTile))
				{
					if (method_->CanMove(leftFrontTile) && method_->isExist(leftFrontTile))
						neighbours.push_back(std::make_pair(leftFront, leftFrontTile));
				}

				//�ҷ�
				AStarDirection right = RotateDirection(parentDirection, 2);
				AStarDirection rightFront = RotateDirection(parentDirection, 1);

				AStarTileSharedPtr rightTile = Tile::CreateTileFromDirection(current, right);
				AStarTileSharedPtr rightFrontTile = Tile::CreateTileFromDirection(current, rightFront);

				if (!method_->CanMove(rightTile) || !method_->isExist(rightTile))
				{
					if (method_->CanMove(rightFrontTile) && method_->isExist(rightFrontTile))
						neighbours.push_back(std::make_pair(rightFront, rightFrontTile));
				}
			}
		}

		return neighbours;
	}
}