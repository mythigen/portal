<script>
  export let href = '';
  export let active = false;
</script>

<li>
  <a {href} class="w-20 h-16 mb-3.5 flex flex-col items-center justify-center group">
    <span 
      class="icon h-8 w-14 flex items-center justify-center mb-1 rounded-full"
      style="background-color: {active ? '#E1F5FE' : ''}; --hover-background-color: {active ? '#E1F5FE' : '#BDBDBD'};"
    >
      <slot name="icon" />
    </span>
    <span class="text-xs block text-center mb-1">
      <slot name="label" />
    </span>
  </a>
</li>

<style>
  li {
    transition: background-color 0.2s;
  }
  /*.icon {
    background-color: var(--bakground-color);
  }*/
  a:hover .icon {
    background: var(--hover-background-color);
  }

  .icon:hover {
    background: var(--hover-background-color);
  }
</style>
