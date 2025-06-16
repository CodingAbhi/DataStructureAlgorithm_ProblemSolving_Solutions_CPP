def key_generation(key_mode, roles):
    # Permission sets for different categories
    all_access = {
        "payments": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent", 
                     "update_dispute", "create_dispute", "read_dispute", "create_refund", "cancel_refund", "read_refund"],
        "banking": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "identity": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "climate": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "capital": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"]
    }

    # Read-only permissions
    read_access = {
        "payments": ["read_settings", "read_intent", "read_dispute", "read_refund"],
        "banking": ["read_settings", "read_intent"],
        "identity": ["read_settings", "read_intent"],
        "climate": ["read_settings", "read_intent"],
        "capital": ["read_settings", "read_intent"]
    }

    # Role-based permissions
    role_permissions = {
        "admin": set(),
        "admin_readonly": set()
    }

    # Assign full permissions to 'admin' role
    for category, perms in all_access.items():
        role_permissions["admin"].update([f"{category}.{perm}" for perm in perms])

    # Assign read-only permissions to 'admin_readonly' role
    for category, perms in read_access.items():
        role_permissions["admin_readonly"].update([f"{category}.{perm}" for perm in perms])

    # Create role permissions for each category with all-access
    for category in all_access.keys():
        role_permissions[category] = set([f"{category}.{perm}" for perm in all_access[category]])

    # Collect permissions for specified roles
    assigned_permissions = set()
    for role in roles:
        if role in role_permissions:
            assigned_permissions.update(role_permissions[role])

    # Output permissions or generate a binary token based on key_mode
    if key_mode == "permissions":
        for perm in sorted(assigned_permissions):
            print(perm)
    elif key_mode == "full_token":
        binary_token = ""
        for category in sorted(all_access.keys()):
            for perm in all_access[category]:
                if f"{category}.{perm}" in assigned_permissions:
                    binary_token += "1"
                else:
                    binary_token += "0"
        print(binary_token)







#
# Complete the 'key_generation' function below.
#
# The function is expected to return a STRING.
# The function accepts following parameters:
#  1. STRING key_mode
#  2. STRING_ARRAY roles
#

def key_generation(key_mode, roles):

    all_access = {
        "payments": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent", 
                     "update_dispute", "create_dispute", "read_dispute", "create_refund", "cancel_refund", "read_refund"],
        "banking": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "identity": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "climate": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"],
        "capital": ["read_settings", "read_intent", "write_settings", "create_intent", "confirm_intent"]
    }

    read_access = {
        "payments": ["read_settings", "read_intent", "read_dispute", "read_refund"],
        "banking": ["read_settings", "read_intent"],
        "identity": ["read_settings", "read_intent"],
        "climate": ["read_settings", "read_intent"],
        "capital": ["read_settings", "read_intent"]
    }
        
    role_permissions = {"admin": set(), "admin_readonly": set()}
                
                
    for category, perms in all_access.items():
        role_permissions["admin"].update([f"{category}.{perm}" for perm in perms])
                        
                        
    for category, perms in read_access.items():
        role_permissions["admin_readonly"].update([f"{category}.{perm}" for perm in perms])
                                
                                
    for category in all_access.keys():
        role_permissions[category] = set([f"{category}.{perm}" for perm in all_access[category]])
                                        
    assigned_permissions = set()
    for role in roles:
        if role in role_permissions:
            assigned_permissions.update(role_permissions[role])
                                                
                                                
    if key_mode == "permissions":
        for perm in sorted(assigned_permissions):
            print(perm)
    elif key_mode == "full_token":
        binary_token = ""
        for category in sorted(all_access.keys()):
            for perm in all_access[category]:
                if f"{category}.{perm}" in assigned_permissions:
                    binary_token += "1"
                else:
                    binary_token += "0"
                                            
        print(binary_token)
    
        
