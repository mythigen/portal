<script>
  import { User, Settings, History } from 'lucide-svelte'; // Importing Lucide icons
  import Li from '../../lib/components/material/li.svelte';
  
  let activeSection = 'settings'; // Track which section is active
  
  function setActiveSection(section) {
    activeSection = section;
    // Here, you could navigate or trigger specific actions for each section
  }
</script>


<div class="flex">
  <nav class="flex w-[88px] h-dvh flex items-center justify-center bg-[#f2ecee]">
    <ul class="gap-[20px] flex flex-col">
      <Li href="?/home" active>
        <svelte:fragment slot="icon">
          <User size="24" />
        </svelte:fragment>
        <svelte:fragment slot="label">User</svelte:fragment>
      </Li>
      <Li href="?/settings">
        <svelte:fragment slot="icon">
          <Settings size="24" />
        </svelte:fragment>
        <svelte:fragment slot="label">Settings</svelte:fragment>
      </Li>
      <Li href="?/history">
        <svelte:fragment slot="icon">
          <History size="24" />
        </svelte:fragment>
        <svelte:fragment slot="label">History</svelte:fragment>
      </Li>
    </ul>
  </nav>

  <main>
    <slot />
    {#if activeSection === 'user'}
      <h1>User</h1>
      <p>Here you can manage your user profile</p>
    {/if}
  
    {#if activeSection === 'settings'}
      <h1>Settings</h1>
      <p>Here you can manage your app settings</p>
    {/if}
  
    {#if activeSection === 'history'}
      <h1>History</h1>
      <p>Here you can see your browsing history</p>
    {/if}
  </main>
</div>
