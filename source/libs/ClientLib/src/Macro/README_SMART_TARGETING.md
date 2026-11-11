# Smart Targeting System for Clean Project

## Tổng quan

Hệ thống Smart Targeting đã được tích hợp vào dự án Clean để cải thiện logic chọn mục tiêu tấn công, tương tự như RSBot. Hệ thống này cung cấp:

- **Emergency Targeting**: Tự động chọn monster đang tấn công player
- **Priority-based Selection**: Ưu tiên monster theo rarity, level, và khoảng cách
- **Blacklist System**: Tránh lặp lại lỗi với monster gặp vấn đề
- **Obstacle Detection**: Phát hiện monster bị che khuất
- **Configurable Options**: Có thể tùy chỉnh các tham số

## Tính năng chính

### 1. Emergency Targeting
- Tự động phát hiện monster đang tấn công player
- Ưu tiên cao nhất trong hệ thống target selection
- Có thể bật/tắt thông qua checkbox "Prioritize Attackers"

### 2. Smart Priority System
- **Attack Weaker First**: Ưu tiên monster yếu (General > Elite > Unique > Giant > Champion)
- **Distance-based**: Ưu tiên monster gần nhất nếu cùng rarity
- **Configurable**: Có thể tùy chỉnh thứ tự ưu tiên

### 3. Blacklist System
- Tự động blacklist monster gặp vấn đề (ví dụ: bị che khuất)
- Timeout 5 giây trước khi remove khỏi blacklist
- Tránh lặp lại lỗi với cùng một monster

### 4. Obstacle Detection
- Phát hiện monster bị che khuất bởi vật cản
- Tự động bỏ qua monster không thể tiếp cận
- Cải thiện hiệu suất hunting

## Cách sử dụng

### 1. Bật Smart Targeting
```cpp
// Trong UI, check vào "Smart Targeting Enabled"
SmartTargetingCheckBox->SetCheckBoxState(true);
```

### 2. Cấu hình các tùy chọn
```cpp
// Ưu tiên monster yếu trước
AttackWeakerFirstCheckBox->SetCheckBoxState(true);

// Tránh monster Elite trở lên
AvoidEliteMonstersCheckBox->SetCheckBoxState(true);

// Ưu tiên monster đang tấn công
PrioritizeAttackersCheckBox->SetCheckBoxState(true);
```

### 3. Tích hợp vào Auto Hunt
```cpp
void CIFMacroMenuAutoHunt::StartAutoHunt()
{
    // ... existing code ...
    
    // Smart targeting system
    if (SmartTargetingCheckBox && SmartTargetingCheckBox->GetCheckedState_MAYBE())
    {
        SmartTargetSelection();
    }
    
    // ... rest of existing code ...
}
```

## Cấu trúc Code

### Header File (IFMacroMenuAutoHunt.h)
```cpp
class CIFMacroMenuAutoHunt : public CIFWnd
{
private:
    // Smart targeting system
    std::map<uint, int> m_blacklistedMonsters;
    CICharactor* m_lastSelectedTarget;
    bool m_emergencyMode;
    
    // Target selection methods
    CICharactor* GetNearestEnemy();
    CICharactor* GetEmergencyTarget();
    CICharactor* GetBestTarget();
    // ... other methods
};
```

### Implementation (IFMacroMenuAutoHunt.cpp)
```cpp
void CIFMacroMenuAutoHunt::SmartTargetSelection()
{
    // Clean up blacklist
    CleanupBlacklist();
    
    // Check emergency situation first
    CICharactor* emergencyTarget = GetEmergencyTarget();
    if (emergencyTarget) {
        // Handle emergency target
        return;
    }
    
    // Get best target based on priority
    CICharactor* bestTarget = GetBestTarget();
    if (bestTarget) {
        // Select best target
    }
}
```

## Tùy chỉnh

### 1. Thêm UI Controls
Bạn cần thêm các controls vào file resource `ifmacromenuautohunt.txt`:

```
110: SmartTargetingCheckBox (CheckBox)
111: AttackWeakerFirstCheckBox (CheckBox)  
112: AvoidEliteMonstersCheckBox (CheckBox)
113: PrioritizeAttackersCheckBox (CheckBox)
114: TargetPriorityList (PopupList)
```

### 2. Điều chỉnh Constants
Trong `SmartTargetingHelper.h`:
```cpp
#define ELITE_MONSTER_LEVEL 40
#define UNIQUE_MONSTER_LEVEL 60
#define GIANT_MONSTER_LEVEL 80
#define CHAMPION_MONSTER_LEVEL 100
#define ATTACK_RANGE 150
#define OBSTACLE_DISTANCE 200
#define BLACKLIST_TIMEOUT_MS 5000
```

### 3. Cải thiện Monster Detection
```cpp
int GetMonsterRarity(CICharactor* monster)
{
    // Implement based on your game's monster data structure
    // You may need to check monster type, name, or other properties
}
```

## So sánh với RSBot

| Tính năng | Clean (Cũ) | Clean (Mới) | RSBot |
|-----------|-------------|--------------|-------|
| Target Selection | Đơn giản (khoảng cách) | Thông minh (priority-based) | Thông minh (priority-based) |
| Emergency Handling | Không có | Có | Có |
| Blacklist System | Không có | Có | Có |
| Obstacle Detection | Không có | Có | Có |
| Performance | Cao (C++) | Cao (C++) | Trung bình (C#) |
| Flexibility | Thấp | Cao | Cao |

## Lưu ý quan trọng

1. **Resource File**: Đảm bảo thêm các UI controls vào file resource
2. **Monster Data**: Cần implement `GetMonsterRarity()` dựa trên cấu trúc dữ liệu game
3. **Entity Management**: Cần tích hợp với hệ thống quản lý entity hiện có
4. **Testing**: Test kỹ lưỡng trước khi deploy production

## Kết luận

Hệ thống Smart Targeting mới đã nâng cấp dự án Clean từ logic đơn giản lên hệ thống thông minh tương đương RSBot, trong khi vẫn giữ được hiệu suất cao của C++. Hệ thống này cung cấp:

- **Tính năng tương đương RSBot**: Emergency handling, blacklist, priority system
- **Hiệu suất cao**: Sử dụng C++ native, tối ưu hóa cho game client
- **Dễ tùy chỉnh**: Có thể điều chỉnh các tham số theo nhu cầu
- **Tích hợp mượt mà**: Không ảnh hưởng đến code hiện có

Với những cải tiến này, dự án Clean giờ đây có thể cạnh tranh với RSBot về mặt tính năng và vượt trội về hiệu suất.
