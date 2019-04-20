gameObject = 
{
    name = "BadGuy",
    initial_position = {x=200,y=0},
    initial_velocity = {x=-100,y=0},
    physics_settings = {
        mass = 1,
        force = {x=0, y=0},
        dragness = 0,
        AABB = 
        {
            center = {x=64, y=64},
            extends = {x=64, y=64}
        },
        collidable = true
    },
    render_settings = {
        sprite_name = "Data\\BoundingBox_Normal.dds",
        sprite_size = {x=256, y=256}
    }
}