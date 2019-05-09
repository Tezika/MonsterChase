gameObject = 
{
    name = "Ball",
    initial_position = {x=0,y=-150},
    initial_velocity = {x=-100,y=100},
    physics_settings = {
        mass = 1,
        force = {x=0, y=0},
        dragness = 0,
        AABB = 
        {
            center = {x=8, y=8},
            extends = {x=8, y=8}
        },
        collidable = true,
        reflectable = true
    },
    render_settings = {
        sprite_name = "Data\\BoundingBox_Normal.dds",
        sprite_size = {x=256, y=256}
    }
}