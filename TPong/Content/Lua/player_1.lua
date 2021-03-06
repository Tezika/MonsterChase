gameObject = 
{
    name = "Player_1",
    initial_position = {x=-340,y=100},
    initial_velocity = {x=0,y=0},
    physics_settings = {
        mass = 1,
        force = {x=0, y=0},
        dragness = 0.00005,
        AABB = 
        {
            center = {x=0, y=64},
            extends = {x=8, y=64}
        },
        collidable = true,
        reflectable = true
    },
    render_settings = {
        sprite_name = "Content\\Bat.dds",
        sprite_size = {x=256, y=256}
    }
}