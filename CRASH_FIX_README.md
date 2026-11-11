# Sửa Lỗi Crash Game - Auto Skill Bot

## Vấn đề
Khi sử dụng auto skill bot, game bị crash khi mở hòm đồ, đặc biệt là các slot 6 và 7 bị lỗi. Ngay cả khi dừng bot, vấn đề vẫn tồn tại và phải xóa 2 món đồ ở slot 6 và 7 mới được.

## Nguyên nhân
Vấn đề nằm ở việc thiếu kiểm tra null pointer khi truy cập các slot equipment và entity manager. Khi bot sử dụng vũ khí và khiên, nó có thể gây ra lỗi memory corruption hoặc truy cập vào vùng nhớ không hợp lệ.

## Giải pháp đã áp dụng

### 1. Thêm kiểm tra null pointer cho slot 6 và 7
- Trong hàm `CheckSkillWeaponSlots()`, thêm kiểm tra null pointer trước khi truy cập slot 6
- Kiểm tra `slot6Item == NULL` và `slot6Item->GetItemData() == NULL`

### 2. Thêm kiểm tra an toàn cho Entity Manager
- Kiểm tra `g_pGfxEttManager == NULL` trước khi truy cập entities
- Kiểm tra `it->second == NULL` trong vòng lặp entities
- Kiểm tra `GetRuntimeClass() == NULL` trước khi truy cập class name

### 3. Thêm kiểm tra cho các hàm chính
- `GetNearMonsterID()`: Kiểm tra null pointer cho Hunt, entities, và monster objects
- `GetNearPartyDeadMemberID()`: Kiểm tra null pointer cho tất cả character objects
- Các hàm khác: Thêm kiểm tra tương tự

### 4. Thêm macro kiểm tra an toàn
```cpp
#define SAFE_CHECK(ptr) if((ptr) == NULL) return 0
#define SAFE_CHECK_CONTINUE(ptr) if((ptr) == NULL) continue
#define SAFE_CHECK_RETURN(ptr, ret) if((ptr) == NULL) return (ret)
```

## Cách sử dụng

### Trước khi sửa
1. Game bị crash khi mở hòm đồ
2. Slot 6 và 7 bị lỗi
3. Phải xóa món đồ để khắc phục

### Sau khi sửa
1. Bot sẽ tự động kiểm tra null pointer
2. Không còn crash game khi mở hòm đồ
3. Slot 6 và 7 hoạt động bình thường
4. Bot an toàn hơn và ổn định hơn

## Lưu ý
- Cần compile lại project sau khi sửa
- Kiểm tra log để đảm bảo không có lỗi mới
- Test kỹ các chức năng auto skill trước khi sử dụng

## Tác giả
AI Assistant - Giải quyết vấn đề crash game auto skill bot
